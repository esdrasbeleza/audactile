#ifndef COLLECTIONSERVICE_H
#define COLLECTIONSERVICE_H

#include <QObject>
#include <QFileSystemWatcher>
#include "../settings/applicationsettings.cpp"

class CollectionService : public QObject
{
Q_OBJECT
public:
    explicit CollectionService(QObject *parent = 0);

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
