#ifndef COLLECTIONTREEWIDGET_H
#define COLLECTIONTREEWIDGET_H

#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include <QSqlTableModel>
#include "../../../music.h"
#include "../../../iconfactory.h"
#include "../../../collection/collectionservice.h"
#include "collectiontreewidgetitem.h"

class CollectionTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    CollectionTreeWidget();
    QTreeWidgetItem *addArtist(QString artist);
    QTreeWidgetItem *addAlbum(QString artist, QString album);
    bool removeArtist(QString artist);
    bool removeAlbum(QString artist, QString album);
    bool removeMusic(QString artist, QString album, QString music);
    bool removeMusic(QString path);

private:
    QStringList toColumns(QString string);
    enum TreeLevel { LevelNone = 0, LevelArtist = 1, LevelAlbum = 2, LevelMusic = 3 };
    void cleanUp(QTreeWidgetItem *parent, CollectionTreeWidget::TreeLevel level);
    CollectionService *service;


private slots:
    CollectionTreeWidgetItem *addMusic(Music *music);



};

#endif // COLLECTIONTREEWIDGET_H
