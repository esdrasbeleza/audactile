#ifndef COLLECTIONTREEWIDGET_H
#define COLLECTIONTREEWIDGET_H

#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include <QSqlTableModel>
#include <QMouseEvent>
#include "../../../music.h"
#include "../../../iconfactory.h"
#include "../../../collection/collectionservice.h"
#include "collectiontreewidgetitem.h"

class CollectionTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    CollectionTreeWidget();
    QTreeWidgetItem *addArtist(QString artist, unsigned int id = 0);
    QTreeWidgetItem *addAlbum(QString artist, QString album, unsigned int albumId = 0);
    QList<CollectionTreeWidgetItem*> musicList;
    bool removeArtist(QString artist);
    bool removeAlbum(QString artist, QString album);
    enum TreeLevel { LevelNone = 0, LevelArtist = 1, LevelAlbum = 2, LevelMusic = 3 };

private:
    QStringList toColumns(QString string);
    void cleanUp(QTreeWidgetItem *parent, int level);
    CollectionService *service;

    // Override drag and drop methods
    void mouseMoveEvent(QMouseEvent *event);


private slots:
    CollectionTreeWidgetItem *addMusic(Music *music,  unsigned int id = 0);
    bool removeMusic(unsigned int id);
    void doubleClickAt(QModelIndex);
    void showChildrenOf(QModelIndex index);

signals:
    void askToAddItemToPlaylist(QList<QUrl>);
    void scanning();
    void listUpdated();


};

#endif // COLLECTIONTREEWIDGET_H
