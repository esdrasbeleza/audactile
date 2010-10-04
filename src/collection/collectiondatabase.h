#ifndef COLLECTIONDATABASE_H
#define COLLECTIONDATABASE_H

#include <QObject>
#include <QDir>
#include <QDesktopServices>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDriver>
#include <QDateTime>
#include <QSqlTableModel>
#include "../music.h"

class CollectionDatabase : public QObject
{
Q_OBJECT
public:
    explicit CollectionDatabase(QObject *parent = 0);
    void addArtist(QString artistName);
    void addAlbum(QString artistName, QString albumName);
    bool addOrUpdateMusic(Music *music);
    void removeArtist(QString artistName);
    void removeAlbum(QString artistName, QString albumName);
    void removeMusic(Music *music);
    void removeMusic(QString path);
    QSqlTableModel *collectionModel();
    QSqlTableModel *artistModel();
    QSqlTableModel *albumModel();
    QSqlTableModel *musicModel();

signals:

public slots:

private:
    QSqlDatabase db;
    void createDatabase();

};

#endif // COLLECTIONDATABASE_H
