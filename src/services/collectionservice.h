#ifndef COLLECTIONSERVICE_H
#define COLLECTIONSERVICE_H

#include <QObject>
#include <QFileSystemWatcher>
#include "../settings/applicationsettings.h"
#include "../collection/collectiondatabase.h"

class CollectionService : public QObject
{
Q_OBJECT
public:
    explicit CollectionService(QObject *parent = 0);
    void refresh();
    void scan();

signals:

private:
    QFileSystemWatcher *watcher;
    CollectionDatabase *collectionDb;
    void scanRecursive(QString path);

public slots:
    void setPaths(QStringList paths);

private slots:
    void fileChanged(QString path);
    void dirChanged(QString path);


};

#endif // COLLECTIONSERVICE_H
