#ifndef COLLECTIONDATABASE_H
#define COLLECTIONDATABASE_H

#include <QMutex>
#include <QObject>
#include <QDir>
#include "collectionitem.h"

class CollectionDatabase : public QObject
{
Q_OBJECT
public:
    static CollectionDatabase* instance();
    void scanDirectory(QDir directory);

private:
    static CollectionDatabase* m_Instance;
    CollectionDatabase(QObject *parent);
    CollectionDatabase(const CollectionDatabase&, QObject *parent);
    CollectionDatabase& operator=(const CollectionDatabase&);

    void addToDatabase();

signals:

public slots:
    void addSong(CollectionItem *validFile);

};

#endif // COLLECTIONDATABASE_H
