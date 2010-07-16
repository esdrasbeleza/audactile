#ifndef COLLECTIONTREEWIDGET_H
#define COLLECTIONTREEWIDGET_H

#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include "../../../iconfactory.h"

class CollectionTreeWidget : public QTreeWidget
{

public:
    CollectionTreeWidget();
    QTreeWidgetItem *addArtist(QString artist);
    QTreeWidgetItem *addAlbum(QString artist, QString album);
    QTreeWidgetItem *addMusic(QString artist, QString album, QString music);
    bool removeArtist(QString artist);
    bool removeAlbum(QString artist, QString album);
    bool removeMusic(QString artist, QString album, QString music);
private:
    QStringList toColumns(QString string);
    enum TreeLevel { LevelNone = 0, LevelArtist = 1, LevelAlbum = 2, LevelMusic = 3 };
    void cleanUp(QTreeWidgetItem *parent, CollectionTreeWidget::TreeLevel level);

};

#endif // COLLECTIONTREEWIDGET_H
