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
#include <QSqlRelationalTableModel>
#include "../music.h"

class CollectionDatabase : public QObject
{
Q_OBJECT
public:
    explicit CollectionDatabase(QObject *parent = 0);
    void addArtist(QString artistName);
    void addAlbum(QString artistName, QString albumName);
    void addOrUpdateMusic(Music *music);
    void addOrUpdateMusic(QString path);
    void removeArtist(QString artistName);
    void removeAlbum(QString artistName, QString albumName);
    void removeMusic(Music *music);
    void removeMusic(QString path);
    QSqlRelationalTableModel *model();

signals:

public slots:

private:
    QSqlDatabase db;
    void createDatabase();


    QSqlRelationalTableModel *artistModel;
    QSqlRelationalTableModel *albumModel;
    QSqlRelationalTableModel *musicModel;

};

#endif // COLLECTIONDATABASE_H
