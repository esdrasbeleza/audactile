#ifndef COLLECTIONTREEWIDGETITEM_H
#define COLLECTIONTREEWIDGETITEM_H

#include <QTreeWidgetItem>
#include <QUrl>
#include <QSqlTableModel>

class CollectionTreeWidgetItem : public QTreeWidgetItem
{
public:
    // TODO: use TreeLevel instead of unsigned int
    explicit CollectionTreeWidgetItem(unsigned int level, unsigned int id, QTreeWidget *parent = 0);
    unsigned int  getNodeLevel();
    unsigned int getId();
    QList<QUrl> getUrlList(QSqlTableModel *collectionModel);

private:
    unsigned int level;
    unsigned int id;

signals:

public slots:

};

#endif // COLLECTIONTREEWIDGETITEM_H
