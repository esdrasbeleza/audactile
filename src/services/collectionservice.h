#ifndef COLLECTIONSERVICE_H
#define COLLECTIONSERVICE_H

#include <QObject>
#include <QFileSystemWatcher>
#include "../settings/applicationsettings.h"

class CollectionService : public QObject
{
Q_OBJECT
public:
    explicit CollectionService(QObject *parent = 0);
    void refresh();

signals:

private:
    QFileSystemWatcher *watcher;

public slots:
    void setPaths(QStringList paths);

private slots:
    void fileChanged(QString path);
    void dirChanged(QString path);


};

#endif // COLLECTIONSERVICE_H
