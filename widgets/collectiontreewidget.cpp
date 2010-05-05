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
}

QStringList CollectionTreeWidget::toColumns(QString string) {
    QStringList columns;
    columns.append(string);
    columns.append(QString::number(topLevelItemCount() + 1));
    return columns;
}


void CollectionTreeWidget::addArtist(QString artist) {
    if (findItems(artist, Qt::MatchExactly, 0).isEmpty()) {
        QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, toColumns(artist));

        // Set font to bold
        QFont font = item->font(0);
        font.setBold(true);
        item->setFont(0, font);

        // Set icon
        item->setIcon(0, QIcon::fromTheme("folder"));

        insertTopLevelItem(0, item);
        sortItems(0, Qt::AscendingOrder);
    }
}


void CollectionTreeWidget::addAlbum(QString artist, QString album) {
    // Looks for the artist
    QList<QTreeWidgetItem*> artistList = findItems(artist, Qt::MatchExactly, 0);
    // If the artist was not found, add it
    if (artistList.isEmpty()) {
        addArtist(artist);
        artistList = findItems(artist, Qt::MatchExactly, 0);
    }

    // Create our new album node and add it
    QTreeWidgetItem *newAlbumNode = new QTreeWidgetItem((QTreeWidget*)0, toColumns(album));

    // Set icon
    newAlbumNode->setIcon(0, QIcon::fromTheme("media-cdrom"));

    artistList.first()->addChild(newAlbumNode);
}
