#include "collectionservice.h"


CollectionService::CollectionService(QObject *parent) :
    QObject(parent)
{
    CollectionHandler *handler = new CollectionHandler();
    t = new QThread();
    connect(this, SIGNAL(scan()), handler, SLOT(scan()));
    handler->moveToThread(t);
}

void CollectionService::start() {
    t->start();
    emit scan();
}
