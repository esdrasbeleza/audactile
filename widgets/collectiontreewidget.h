#ifndef COLLECTIONTREEWIDGET_H
#define COLLECTIONTREEWIDGET_H

#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>

class CollectionTreeWidget : public QTreeWidget
{
public:
    CollectionTreeWidget();
    QTreeWidgetItem* addArtist(QString artist);
    QTreeWidgetItem* addAlbum(QString artist, QString album);
    QTreeWidgetItem* addMusic(QString artist, QString album, QString music);
private:
    QStringList toColumns(QString string);
};

#endif // COLLECTIONTREEWIDGET_H
