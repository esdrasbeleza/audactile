#ifndef COLLECTIONTREEWIDGETSONG_H
#define COLLECTIONTREEWIDGETSONG_H

#include "collectiontreewidgetitem.h"
#include "../../../iconfactory.h"
#include "../../../music.h"

class CollectionTreeWidgetSong : public CollectionTreeWidgetItem
{
public:
    CollectionTreeWidgetSong(Music *music, unsigned int id = 0, QTreeWidget *parent = 0);
    QList<QUrl> getUrlList();
    Music getMusic();

private:
    Music music;
};

#endif // COLLECTIONTREEWIDGETSONG_H
