#ifndef COLLECTIONTREEVIEW_H
#define COLLECTIONTREEVIEW_H

#include <QTreeView>
#include <QHeaderView>
#include "../../../collection/collectionservice.h"

class CollectionTreeView : public QTreeView
{
Q_OBJECT
public:
    explicit CollectionTreeView(QWidget *parent = 0);

signals:

public slots:

private:
    CollectionService *service;

};

#endif // COLLECTIONTREEVIEW_H
