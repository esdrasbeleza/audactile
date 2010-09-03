#ifndef COLLECTIONHANDLER_H
#define COLLECTIONHANDLER_H

#include <QObject>
#include <QFileSystemWatcher>
#include "../settings/applicationsettings.h"
#include "../collection/collectiondatabase.h"

class CollectionHandler : public QObject
{
Q_OBJECT
public:
    explicit CollectionHandler(QObject *parent = 0);
    void refresh();

signals:

private:
    QFileSystemWatcher *watcher;
    CollectionDatabase *collectionDb;
    void scanRecursive(QString path);

public slots:
    void scan();
    void setPaths(QStringList paths);

private slots:
    void fileChanged(QString path);
    void dirChanged(QString path);


};

#endif // COLLECTIONHANDLER_H
