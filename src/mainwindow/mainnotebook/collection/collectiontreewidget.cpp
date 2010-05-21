#include "collectiontreewidget.h"


// TODO: cleanup

/// @brief Constructor
CollectionTreeWidget::CollectionTreeWidget()
{
    setColumnCount(2);
    header()->hide(); // hide headers
    hideColumn(1); // hide id column

    addArtist("Artista 1");
    addArtist("Artista 1");
    addArtist("Artista 1");
    addArtist("Artista 2");
    addAlbum("Artista 1", "Album 1");
    addAlbum("Artista 3", "Album 1");
    addAlbum("Artista 3", "Album 1");
    addAlbum("Artista 3", "Album 1");
    addAlbum("Artista 3", "Album 2");
    addMusic("Artista 2", "Album 1 do artista 2", "Musica 1");
    addMusic("Artista 2", "Album 1 do artista 2", "Musica 2");
    addMusic("Artista 4", "Album 1 do artista 4", "Musica 1");
    addMusic("Artista 4", "Album 1 do artista 4", "Musica 2");
    addMusic("Artista 4", "Album 1 do artista 4", "Musica 3");
    addMusic("Artista 4", "Album 2 do artista 4", "Musica 1");
    addMusic("Artista 4", "Album 2 do artista 4", "Musica 2");
    addMusic("Artista 4", "Album 2 do artista 4", "Musica 3");
    addAlbum("Artista 5", "Album 1");
    addAlbum("Artista 5", "Album 2");
    removeAlbum("Artista 3", "Album 1");
    removeMusic("Artista 5", "Album 2 do artista 4", "Musica 3");
    removeMusic("Artista 4", "Album 2 do artista 4", "Musica 3");

    cleanUp(NULL, CollectionTreeWidget::LevelNone);
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
        item->setIcon(0, QIcon::fromTheme("folder"));

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
    newAlbumNode->setIcon(0, QIcon::fromTheme("media-cdrom"));

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


QTreeWidgetItem *CollectionTreeWidget::addMusic(QString artist, QString album, QString music) {
    // Looks for the album
    QTreeWidgetItem *newMusicNode; // The node with the music, whether it exists or not
    QTreeWidgetItem *albumItem = addAlbum(artist, album);

    // Look for music
    for (int i = 0; i < albumItem->childCount(); i++) {
        if (albumItem->child(i)->text(0) == music) {
            newMusicNode = albumItem->child(i);
            return newMusicNode;
        }
    }

    // Create our new music node and add it if it was not found
    newMusicNode = new QTreeWidgetItem((QTreeWidget*)0, toColumns(music));

    // Set icon
    newMusicNode->setIcon(0, QIcon::fromTheme("sound"));

    albumItem->addChild(newMusicNode);
    albumItem->sortChildren(0, Qt::AscendingOrder);

    return newMusicNode;
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
                delete albumItem->child(i);
                cleanUp(albumItem, CollectionTreeWidget::LevelAlbum);
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
    }

}
