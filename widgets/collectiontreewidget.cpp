#include "collectiontreewidget.h"


/*
 * TODO:
 * - Criar metodo de adicao de musica
 * - Criar metodos de remocao
 */

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
}

QStringList CollectionTreeWidget::toColumns(QString string) {
    QStringList columns;
    columns.append(string);
    columns.append(QString::number(topLevelItemCount() + 1));
    return columns;
}


QTreeWidgetItem* CollectionTreeWidget::addArtist(QString artist) {
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


QTreeWidgetItem* CollectionTreeWidget::addAlbum(QString artist, QString album) {
    qDebug("Adding album");

    // Looks for the artist
    QTreeWidgetItem* newAlbumNode; // The node with the album, whether it exists or not
    QTreeWidgetItem* artistItem;
    artistItem = addArtist(artist);

    // Look for album
    for (int i = 0; i < artistItem->childCount(); i++) {
        qDebug("Iterating!");
        if (artistItem->child(i)->text(0) == album) {
            qDebug("Album found!");
            newAlbumNode = artistItem->child(i);
            return newAlbumNode;
        }
    }

    // Create our new album node and add it if it was not found
    newAlbumNode = new QTreeWidgetItem((QTreeWidget*)0, toColumns(album));

    // Set icon
    newAlbumNode->setIcon(0, QIcon::fromTheme("media-cdrom"));

    artistItem->addChild(newAlbumNode);
    sortItems(0,Qt::AscendingOrder);

    qDebug("Album added");

    return newAlbumNode;
}


QTreeWidgetItem* CollectionTreeWidget::addMusic(QString artist, QString album, QString music) {
    qDebug("Adding music");

    // Looks for the album
    QTreeWidgetItem* newMusicNode; // The node with the music, whether it exists or not
    QTreeWidgetItem* albumItem = addAlbum(artist, album);

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
    sortItems(0, Qt::AscendingOrder);

    qDebug("Music added.");
    return newMusicNode;
}
