#include "collectiontreewidget.h"
#include <QMimeData>
#include <QDrag>

// TODO: cleanup

/// @brief Constructor
CollectionTreeWidget::CollectionTreeWidget()
{
    setColumnCount(1);
    header()->hide(); // hide headers
    setDragEnabled(true);
    setAcceptDrops(true);
    setSelectionMode(QAbstractItemView::ExtendedSelection);

    service = new CollectionService();

    // Add songs that currently exist on database
    QSqlTableModel *artistModel = service->artistModel();
    artistModel->select();

    // TODO: verify if we can put fetchmore() inside the for loop.
    // TODO: put this task in background... URGENT
    while (artistModel->canFetchMore()) artistModel->fetchMore();
    int total = artistModel->rowCount();

    for (int i = 0; i < total; i++) {
        QString artist = artistModel->record(i).value(artistModel->fieldIndex("name")).toString();
        unsigned int id = artistModel->record(i).value(artistModel->fieldIndex("id")).toInt();
        addArtist(artist, id);
    }
    delete artistModel;

    /*
     * TODO: modify the slots in order to add only the artist, not the music.
     */
    connect(service, SIGNAL(songAdded(Music*)), this, SLOT(addMusic(Music*)));
    connect(service, SIGNAL(songRemoved(unsigned int)), this, SLOT(removeMusic(uint)));
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClickAt(QModelIndex)));
    connect(this, SIGNAL(expanded(QModelIndex)), this, SLOT(showChildrenOf(QModelIndex)));

    /*
     * We shall emit those signals to show or hide the widget that will
     * give the feedback that the collection is being scanned.
     */
    connect(service, SIGNAL(scanning()), this, SIGNAL(scanning()));
    connect(service, SIGNAL(listUpdated()), this, SIGNAL(listUpdated()));


    // Start service to find new songs and remove the inexistent ones
    service->start(QThread::LowestPriority);

}

QStringList CollectionTreeWidget::toColumns(QString string) {
    QStringList columns;
    columns.append(string);
    columns.append(QString::number(topLevelItemCount() + 1));
    return columns;
}

void CollectionTreeWidget::showChildrenOf(QModelIndex index) {
    CollectionTreeWidgetItem *item = (CollectionTreeWidgetItem*)itemFromIndex(index);

    // If the item pressed was an artist, add albums
    if (item->getNodeLevel() == LevelArtist) {
        QString artist = item->text(0).toUtf8();

        // Looks for artist id
        QString artistId = QString::number(item->getId());

        // Looks for artist albums
        QSqlTableModel *albumModel = service->albumModel();
        albumModel->setFilter("id_artist = " + artistId);
        albumModel->select();

        while (albumModel->canFetchMore()) albumModel->fetchMore();
        int total = albumModel->rowCount();

        for (int i = 0; i < total; i++) {
            QString album = albumModel->record(i).value(albumModel->fieldIndex("title")).toString();
            unsigned int id = albumModel->record(i).value(albumModel->fieldIndex("id")).toInt();
            addAlbum(artist, album, id);
        }

        delete albumModel;
    }
    // If the item pressed was an album, add songs
    else if (item->getNodeLevel() == LevelAlbum) {
        QString albumId = QString::number(item->getId());

        QSqlTableModel *musicModel = service->musicModel();
        musicModel->setFilter("id_album = " + albumId);
        musicModel->setSort(musicModel->fieldIndex("track_number"), Qt::AscendingOrder);
        musicModel->select();

        while (musicModel->canFetchMore()) musicModel->fetchMore();
        int total = musicModel->rowCount();

        for (int i = 0; i < total; i++) {
            QString path = musicModel->record(i).value(musicModel->fieldIndex("path")).toString();
            unsigned int id = musicModel->record(i).value(musicModel->fieldIndex("id")).toInt();

            Music *music = new Music(QUrl(path));
            addMusic(music, id);
            delete music;
        }
    }

    expand(index);
}

QTreeWidgetItem *CollectionTreeWidget::addArtist(QString artist, unsigned int id) {
    // TODO: find in in database if we don't have it

    QList<QTreeWidgetItem*> artistList = findItems(artist, Qt::MatchExactly, 0);
    if (artistList.isEmpty()) {
        CollectionTreeWidgetItem *item = new CollectionTreeWidgetItem(LevelArtist, id, (QTreeWidget*)0);
        item->setText(0, artist);
        item->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

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


QTreeWidgetItem *CollectionTreeWidget::addAlbum(QString artist, QString album, unsigned int albumId) {
    // TODO: find in in database if we don't have it

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
    newAlbumNode = new CollectionTreeWidgetItem(LevelAlbum, albumId, (QTreeWidget*)0);
    newAlbumNode->setText(0, album);
    newAlbumNode->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

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


CollectionTreeWidgetItem *CollectionTreeWidget::addMusic(Music *music, unsigned int id) {
    // Find id in database if we don't have it
    if (id == 0) {
         QSqlTableModel *model = service->collectionModel();

         // SQLite used two single quotes to escape a single quote! :)
         QString filter = "artist = '" + music->getArtist().replace("'","''") + "' AND "
                          "album = '" + music->getAlbum().replace("'","''") + "' AND "
                          "music = " + music->getTitle().replace("'","''") + "'";
         model->setFilter(filter);
         model->select();

         while (model->canFetchMore()) model->fetchMore();
         int total = model->rowCount();
         if (total > 0) {
            id = model->record(0).value(model->fieldIndex("id_music")).toInt();
//            Debug("Music id: " + QString::number(id).toUtf8());
         }
         else {
//             qDebug("ERROR: no songs found! -- " + filter.toUtf8());
             return NULL;
         }
    }

    // Looks for the album
    QTreeWidgetItem *albumItem = addAlbum(music->getArtist(), music->getAlbum());

    // Create our new music node and add it if it was not found
    removeMusic(id);

    CollectionTreeWidgetItem *newMusicNode = new CollectionTreeWidgetItem(LevelMusic, id, (QTreeWidget*)0);
    newMusicNode->setText(0, music->getTitle());
    newMusicNode->setIcon(0, IconFactory::fromTheme("sound"));
    albumItem->addChild(newMusicNode);
    musicList.append(newMusicNode);

    return newMusicNode;
}

bool CollectionTreeWidget::removeMusic(unsigned int id) {
    int total = musicList.count();

    if (total == 0) return false;
    for (int i = 0; i < total; i++) {
        CollectionTreeWidgetItem *item = musicList[i];

        if (item->getId() == id) {
            CollectionTreeWidgetItem *album = (CollectionTreeWidgetItem*)item->parent();
            musicList.removeAt(i);
            delete item;
            cleanUp(album, CollectionTreeWidget::LevelAlbum);
            return true;
        }
    }

    return false;
}

void CollectionTreeWidget::cleanUp(QTreeWidgetItem *parent = NULL, int level = CollectionTreeWidget::LevelNone) {
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
        CollectionTreeWidgetItem *collectionCurrentItem = (CollectionTreeWidgetItem *)currentItem;
        list.append(collectionCurrentItem->getUrlList(service->collectionModel()));
    }

    // mime stuff
    mimeData->setUrls(list);
    drag->setMimeData(mimeData);

    // start drag
    drag->exec(Qt::CopyAction | Qt::MoveAction);
}

void CollectionTreeWidget::doubleClickAt(QModelIndex index) {
    CollectionTreeWidgetItem *item = (CollectionTreeWidgetItem *)itemFromIndex(index);
    if (item->getNodeLevel() == LevelMusic) {
        emit askToAddItemToPlaylist(item->getUrlList(service->collectionModel()));
    }
}
