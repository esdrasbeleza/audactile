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
#include <QSqlRelationalTableModel>
#include "../music.h"

class CollectionDatabase : public QObject
{
Q_OBJECT
public:
    explicit CollectionDatabase(QObject *parent = 0);
    void addArtist(QString artistName);
    void addAlbum(QString artistName, QString albumName);
    void addMusic(Music *music);

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
