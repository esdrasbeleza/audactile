#include "collectiontreeview.h"

CollectionTreeView::CollectionTreeView(QWidget *parent) :
    QTreeView(parent)
{

    service = new CollectionService();
    setModel(service->model());
    service->start();

    header()->hide();
    hideColumn(0);
}
