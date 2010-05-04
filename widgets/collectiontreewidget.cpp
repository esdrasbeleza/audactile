#include "collectiontreewidget.h"

CollectionTreeWidget::CollectionTreeWidget()
{
    setColumnCount(1);
    header()->hide();

    addNewArtist("Artista 1");
    addNewArtist("Artista 1");
    addNewArtist("Artista 1");
    addNewArtist("Artista 2");
    addNewAlbum("Artista 1", "Album 1");
    addNewAlbum("Artista 3", "Album 1");
}


void CollectionTreeWidget::addNewArtist(QString artist) {
    if (findItems(artist, Qt::MatchExactly,0).count() == 0) {
        QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(artist));
        insertTopLevelItem(0, item);
        sortItems(0, Qt::AscendingOrder);
    }
}


void CollectionTreeWidget::addNewAlbum(QString artist, QString album) {
    // Looks for the artist
    QList<QTreeWidgetItem*> artistList = findItems(artist, Qt::MatchExactly,0);

    // If the artist was not found, add it
    if (artistList.isEmpty()) {
        addNewArtist(artist);
        QList<QTreeWidgetItem*> artistList = findItems(artist, Qt::MatchExactly,0);
    }

    // Create our new album node and add it
    QTreeWidgetItem *newAlbum= new QTreeWidgetItem((QTreeWidget*)0, QStringList(album));
    artistList.first()->addChild(newAlbum);
}
