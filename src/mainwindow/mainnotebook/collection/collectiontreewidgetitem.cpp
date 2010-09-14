#include "collectiontreewidgetitem.h"
#include "collectiontreewidgetsong.h"

CollectionTreeWidgetItem::CollectionTreeWidgetItem(TreeLevel level, QTreeWidget *parent) :
    QTreeWidgetItem(parent, 0)
{
    this->level = level;
}

int CollectionTreeWidgetItem::getNodeLevel() {
    return level;
}

QList<QUrl> CollectionTreeWidgetItem::getUrlList() {
    qDebug("CollectionTreeWidgetItem getUrlList");
    QList<QUrl> urlList;

    int childrenTotal = childCount();

    for (int i = 0; i < childrenTotal; i++) {
        CollectionTreeWidgetItem *childNode = (CollectionTreeWidgetItem*)child(i);
        if (childNode->getNodeLevel() > LevelMusic) {
            qDebug("Level " + QString::number(childNode->getNodeLevel()).toUtf8());
            urlList.append(childNode->getUrlList());
        }
        else {
            qDebug("Level " + QString::number(childNode->getNodeLevel()).toUtf8());
            CollectionTreeWidgetSong *song = (CollectionTreeWidgetSong*)childNode;
            urlList.append(song->getUrlList());
        }
    }

    return urlList;
}
