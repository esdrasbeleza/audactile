#include "collectiontreewidget.h"


// TODO: cleanup

/// @brief Constructor
CollectionTreeWidget::CollectionTreeWidget()
{
    setColumnCount(1);
    header()->hide(); // hide headers

    service = new CollectionService();

    // Add songs that currently exist on database
    QSqlTableModel *collectionModel = service->model();
    for (int i = 0; i < collectionModel->rowCount(); i++) {
        QString path = collectionModel->record(i).value(collectionModel->fieldIndex("path")).toString();

        // TODO: this loop sucks!! Improve this!
        Music *music = new Music(QUrl(path));
        addMusic(music);
        delete music;
    }

    cleanUp(NULL, CollectionTreeWidget::LevelNone);

    connect(service, SIGNAL(songAdded(Music*)), this, SLOT(addMusic(Music*)));

    // Start service to find new songs and remove the inexistent ones
    service->start();

}

QStringList CollectionTreeWidget::toColumns(QString string) {
    QStringList columns;
    columns.append(string);
    columns.append(QString::number(topLevelItemCount() + 1));
    return columns;
}


QTreeWidgetItem *CollectionTreeWidget::addArtist(QString artist) {
    QList<QTreeWidgetItem*> artistList = findItems(artist, Qt::MatchExactly, 0);
    if (artistList.isEmpty()) {
        QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, toColumns(artist));

        // Set font to bold
        QFont font = item->font(0);
        font.setBold(true);
        item->setFont(0, font);

        // Set icon
        item->setIcon(0, IconFactory::fromTheme("folder"));

        // Insert item
        insertTopLevelItem(0, item);
        sortItems(0, Qt::AscendingOrder);

        return item;
    }
    else {
        return artistList.first();
    }
}

bool CollectionTreeWidget::removeArtist(QString artist) {
    QList<QTreeWidgetItem*> artistList = findItems(artist, Qt::MatchExactly, 0);
    if (!artistList.isEmpty()) {
        delete artistList.first();
        return true;
    }
    return false;
}


QTreeWidgetItem *CollectionTreeWidget::addAlbum(QString artist, QString album) {
    // Looks for the artist
    QTreeWidgetItem *newAlbumNode; // The node with the album, whether it exists or not
    QTreeWidgetItem *artistItem;
    artistItem = addArtist(artist);

    // Look for album
    for (int i = 0; i < artistItem->childCount(); i++) {
        if (artistItem->child(i)->text(0) == album) {
            newAlbumNode = artistItem->child(i);
            return newAlbumNode;
        }
    }

    // Create our new album node and add it if it was not found
    newAlbumNode = new QTreeWidgetItem((QTreeWidget*)0, toColumns(album));

    // Set icon
    newAlbumNode->setIcon(0, IconFactory::fromTheme("media-cdrom"));

    artistItem->addChild(newAlbumNode);
    artistItem->sortChildren(0, Qt::AscendingOrder);

    return newAlbumNode;
}


bool CollectionTreeWidget::removeAlbum(QString artist, QString album) {
    QList<QTreeWidgetItem*> artistList = findItems(artist, Qt::MatchExactly, 0);
    // If we have no artist, we have no album.
    if (artistList.isEmpty()) {
        return false;
    }

    // Looks for the artist
    QTreeWidgetItem *artistItem = artistList.first();
    // Look for album
    for (int i = 0; i < artistItem->childCount(); i++) {
        if (artistItem->child(i)->text(0) == album) {
            delete artistItem->child(i);
            cleanUp(artistItem, CollectionTreeWidget::LevelArtist);
            return true;
        }
    }
    return false;
}


CollectionTreeWidgetItem *CollectionTreeWidget::addMusic(Music *music) {
    if (!music->isValid()) {
        return NULL;
    }

    // Looks for the album
    QTreeWidgetItem *albumItem = addAlbum(music->getArtist(), music->getAlbum());

    // Create our new music node and add it if it was not found
//    removeMusic(music->getFileUrl().path());
    CollectionTreeWidgetItem *newMusicNode = new CollectionTreeWidgetItem(music, (QTreeWidget*)0);

    albumItem->addChild(newMusicNode);
    albumItem->sortChildren(0, Qt::AscendingOrder);

    return newMusicNode;
}

bool CollectionTreeWidget::removeMusic(QString path) {
    int artistTotal = invisibleRootItem()->childCount();
    if (artistTotal == 0) return false;

    for (int i = 0; i < artistTotal; i++) {
        QTreeWidgetItem *artistNode = invisibleRootItem()->child(i);
        int albumTotal = artistNode->childCount();
        if (albumTotal == 0) { continue; }

        for (int j = 0; j < albumTotal; j++) {
            CollectionTreeWidgetItem *musicNode = (CollectionTreeWidgetItem *)artistNode->child(j);
            qDebug(musicNode->getMusic()->getArtist().toUtf8());
            if (musicNode->getMusic()->getFileUrl().path() == path) {
                delete musicNode;
                return true;
            }
        }
    }
    return false;
}


bool CollectionTreeWidget::removeMusic(QString artist, QString album, QString music) {
    QList<QTreeWidgetItem*> artistList = findItems(artist, Qt::MatchExactly, 0);
    // If we have no artist, we have no album and no music.
    if (artistList.isEmpty()) {
        return false;
    }

    // Looks for the artist
    QTreeWidgetItem *artistItem = artistList.first();
    QTreeWidgetItem *albumItem = NULL;
    // Look for album
    for (int i = 0; i < artistItem->childCount(); i++) {
        if (artistItem->child(i)->text(0) == album) {
            albumItem = artistItem->child(i);
        }
    }

    // If album is null, we have nothing to do here
    if (albumItem != NULL) {
        for (int i = 0; i < albumItem->childCount(); i++) {
            if (albumItem->child(i)->text(0) == music) {
                qDebug("Deleting music");
                delete albumItem->child(i);

                if (albumItem->childCount() == 0) {
                    qDebug("Removing album");
                    delete albumItem;
                }

                return true;
            }
        }
    }

    return false;
}

void CollectionTreeWidget::cleanUp(QTreeWidgetItem *parent = NULL, CollectionTreeWidget::TreeLevel level = CollectionTreeWidget::LevelNone) {
    // If parent is null, process all artists and its children nodes
    if (parent == NULL) {
        cleanUp(invisibleRootItem(), CollectionTreeWidget::LevelNone);
    }

    // if we have a parent, process it
    else {

        // If it's an artist, enter it
        if (level < CollectionTreeWidget::LevelAlbum) {
            int childCount = parent->childCount();
            for (int i = 0; i < childCount; i++) {
                TreeLevel newLevel =  (TreeLevel)(level + 1);
                cleanUp(parent->child(i), newLevel);
            }
        }

        // If it's an album and it has no songs, remove it!
        else {
            if (parent->childCount() == 0) {
                QTreeWidgetItem *parentParent = parent->parent();
                delete parent;

                // If artist has no more albums, remove it too
                if (parentParent->childCount() == 0) delete parentParent;

            }
        }
    }

}
