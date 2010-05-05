#ifndef COLLECTIONTREEWIDGET_H
#define COLLECTIONTREEWIDGET_H

#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>

class CollectionTreeWidget : public QTreeWidget
{
public:
    CollectionTreeWidget();
    void addArtist(QString artist);
    void addAlbum(QString artist, QString album);
private:
    QStringList toColumns(QString string);
};

#endif // COLLECTIONTREEWIDGET_H
