#ifndef COLLECTIONTREEWIDGETITEM_H
#define COLLECTIONTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include "../../../iconfactory.h"
#include "../../../music.h"

class CollectionTreeWidgetItem : public QTreeWidgetItem
{
public:
    explicit CollectionTreeWidgetItem(Music *music, QTreeWidget *parent = 0);
    Music getMusic();

private:
    Music music;

signals:

public slots:

};

#endif // COLLECTIONTREEWIDGETITEM_H
