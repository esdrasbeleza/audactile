#include "collectiontreewidget.h"


// TODO: cleanup

/// @brief Constructor
CollectionTreeWidget::CollectionTreeWidget()
{
    setColumnCount(1);
    header()->hide(); // hide headers
    setDragEnabled(true);
    setAcceptDrops(true);

    // TODO: enable drops to add music to collection

    service = new CollectionService();

    // Add songs that currently exist on database
    QSqlTableModel *collectionModel = service->model();

    while (collectionModel->canFetchMore()) collectionModel->fetchMore();
    int total = collectionModel->rowCount();

    for (int i = 0; i < total; i++) {
        /*
         * Instead of reading all data from database again, we simply read from database
         * in order to avoid memory problems.
         */
        QString artist = collectionModel->record(i).value(collectionModel->fieldIndex("artist")).toString();
        QString album = collectionModel->record(i).value(collectionModel->fieldIndex("album")).toString();
        QString title = collectionModel->record(i).value(collectionModel->fieldIndex("music")).toString();
        QString path = collectionModel->record(i).value(collectionModel->fieldIndex("path")).toString();
        unsigned int trackNumber = collectionModel->record(i).value(collectionModel->fieldIndex("track_number")).toInt();

        qDebug(QString::number(i).toUtf8() + " - Adding " + path.toUtf8());

        Music *music = new Music(artist, album, title, path, trackNumber);
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


CollectionTreeWidgetSong *CollectionTreeWidget::addMusic(Music *music) {
    // Looks for the album
    QTreeWidgetItem *albumItem = addAlbum(music->getArtist(), music->getAlbum());

    // Create our new music node and add it if it was not found
    removeMusic(music->getFileUrl().path());

    CollectionTreeWidgetSong *newMusicNode = new CollectionTreeWidgetSong(music, (QTreeWidget*)0);
    albumItem->addChild(newMusicNode);
    musicList.append(newMusicNode);

    return newMusicNode;
}

bool CollectionTreeWidget::removeMusic(QString path) {
    qDebug("remove " + path.toUtf8());
    int total = musicList.count();

    if (total == 0) return false;
    for (int i = 0; i < total; i++) {
        CollectionTreeWidgetSong *item = musicList[i];
        if (item->getMusic().getFileUrl().path() == path) {
            qDebug("Removing " + path.toUtf8());
            musicList.removeAt(i);
            delete item;
            return true;
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


void CollectionTreeWidget::mouseMoveEvent(QMouseEvent *event) {
    // if not left button - return
    if (!(event->buttons() & Qt::LeftButton)) return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    // construct list of QUrls
    // other widgets accept this mime type, we can drop to them
    QList<QUrl> list;

    foreach (QTreeWidgetItem *currentItem, selectedItems()) {
        CollectionTreeWidgetItem *collectionCurrentItem = static_cast<CollectionTreeWidgetItem *>(currentItem);
        list.append(collectionCurrentItem->getUrlList());
    }

    // mime stuff
    mimeData->setUrls(list);
    drag->setMimeData(mimeData);

    // start drag
    qDebug("Starting drag");
    QList<QTreeWidgetItem *> itemsToRemove = selectedItems();
    drag->exec(Qt::CopyAction | Qt::MoveAction);
}
