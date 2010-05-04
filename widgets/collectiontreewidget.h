#ifndef COLLECTIONTREEWIDGET_H
#define COLLECTIONTREEWIDGET_H

#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>

class CollectionTreeWidget : public QTreeWidget
{
public:
    CollectionTreeWidget();
    void addNewArtist(QString artist);
    void addNewAlbum(QString artist, QString album);

};

#endif // COLLECTIONTREEWIDGET_H
