#include "collectionservice.h"


CollectionService::CollectionService(QObject *parent) :
    QThread(parent)
{
    handler = new CollectionHandler();
}

void CollectionService::run() {
        handler->scan();
}
