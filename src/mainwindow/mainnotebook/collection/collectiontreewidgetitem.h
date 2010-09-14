#ifndef COLLECTIONTREEWIDGETITEM_H
#define COLLECTIONTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include <QUrl>

class CollectionTreeWidgetItem : public QTreeWidgetItem
{
public:
    // TODO: use TreeLevel instead of unsigned int
    explicit CollectionTreeWidgetItem(unsigned int level, QTreeWidget *parent = 0);
    unsigned int  getNodeLevel();
    QList<QUrl> getUrlList();

private:
    unsigned int level;

signals:

public slots:

};

#endif // COLLECTIONTREEWIDGETITEM_H
