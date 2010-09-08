#ifndef COLLECTIONSERVICE_H
#define COLLECTIONSERVICE_H

#include <QThread>
#include <QFileSystemWatcher>
#include "../settings/applicationsettings.h"
#include "../collection/collectiondatabase.h"
#include "../music.h"

class CollectionService : public QThread
{
Q_OBJECT
public:
    explicit CollectionService(QObject *parent = 0);
    void refresh();
    void run();
    QSqlTableModel *model();

signals:
    void listUpdated();
    void songAdded(Music *music);

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

#endif // COLLECTIONSERVICE_H
