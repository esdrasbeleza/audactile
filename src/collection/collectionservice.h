#ifndef COLLECTIONSERVICE_H
#define COLLECTIONSERVICE_H

#include <QObject>
#include <QThread>
#include "collectionhandler.h"

class CollectionService : public QObject
{
Q_OBJECT
public:
    explicit CollectionService(QObject *parent = 0);
    void start();

private:
    QThread *t;

signals:
    void scan();

public slots:

};

#endif // COLLECTIONSERVICE_H
