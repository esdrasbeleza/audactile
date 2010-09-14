#ifndef COLLECTIONTREEWIDGET_H
#define COLLECTIONTREEWIDGET_H

#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include <QSqlTableModel>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
#include "../../../music.h"
#include "../../../iconfactory.h"
#include "../../../collection/collectionservice.h"
#include "collectiontreewidgetitem.h"
#include "collectiontreewidgetsong.h"

class CollectionTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    CollectionTreeWidget();
    QTreeWidgetItem *addArtist(QString artist);
    QTreeWidgetItem *addAlbum(QString artist, QString album);
    QList<CollectionTreeWidgetSong*> musicList;
    bool removeArtist(QString artist);
    bool removeAlbum(QString artist, QString album);
    bool removeMusic(QString artist, QString album, QString music);
    enum TreeLevel { LevelNone = 0, LevelArtist = 1, LevelAlbum = 2, LevelMusic = 3 };

private:
    QStringList toColumns(QString string);
    void cleanUp(QTreeWidgetItem *parent, int level);
    CollectionService *service;

    // Override drag and drop methods
    void mouseMoveEvent(QMouseEvent *event);


private slots:
    CollectionTreeWidgetSong *addMusic(Music *music);
    bool removeMusic(QString path);
    void doubleClickAt(QModelIndex);

signals:
    void askToAddItemToPlaylist(QList<QUrl>);


};

#endif // COLLECTIONTREEWIDGET_H
