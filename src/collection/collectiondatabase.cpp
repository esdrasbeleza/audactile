#include "collectiondatabase.h"

CollectionDatabase::CollectionDatabase(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString database = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + QDir::separator() + "collection.db";
    qDebug("DATABASE: " + database.toUtf8());
    db.setDatabaseName(database);

    createDatabase();

    artistModel = new QSqlRelationalTableModel(this, db);
    artistModel->setTable("artist");
    artistModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    albumModel = new QSqlRelationalTableModel(this, db);
    albumModel->setTable("album");
    albumModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    albumModel->setRelation(albumModel->fieldIndex("id_artist"), QSqlRelation("artist", "id", "name"));

    musicModel = new QSqlRelationalTableModel(this, db);
    musicModel->setTable("music");
    musicModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    musicModel->setRelation(musicModel->fieldIndex("id_album"), QSqlRelation("album", "id", "title"));

}

// TODO: make use of Qt classes to handle databases


void CollectionDatabase::createDatabase() {
    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }

    QStringList tables = db.tables();

    // TODO: use titles as primary key?

    if (!tables.contains("artist")) {
        db.exec("CREATE TABLE artist ("
                "id integer primary key AUTOINCREMENT, "
                "name varchar(120) UNIQUE NOT NULL"
                ")");
    }

    if (!tables.contains("album")) {
        db.exec("CREATE TABLE album ("
                "id integer primary key AUTOINCREMENT, "
                "id_artist int, "
                "title varchar(120) NOT NULL"
                ")");
    }

    if (!tables.contains("music")) {
        db.exec("CREATE TABLE music ("
                "id integer primary key AUTOINCREMENT, "
                "id_album int, "
                "track_number int, "
                "title varchar(120) NOT NULL,"
                "path varchar(2048) UNIQUE NOT NULL"
                ")");
    }

    if (db.lastError().type() != QSqlError::NoError) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }

    db.close();


}

void CollectionDatabase::addArtist(QString artistName) {
    artistModel->setFilter("name =  '" + artistName.toUtf8() + "'");
    artistModel->select();
    qDebug("COUNT: " + QString::number(artistModel->rowCount()).toUtf8());

    // FIXME: rowcount is always 0!
    if (artistModel->rowCount() == 0) {
        db.open();
        qDebug("Adding artist '" + artistName.toUtf8() + "'");
        db.exec("INSERT INTO artist (name) VALUES ('" + artistName + "');");
        db.close();

        if (db.lastError().type() != QSqlError::NoError) {
            qDebug("ERROR! " + db.lastError().text().toUtf8());
        }
    }

}

void CollectionDatabase::addAlbum(QString artistName, QString albumName) {
    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }

    // TODO: verify if album exists
    qDebug("Adding album " + albumName.toUtf8());
    db.exec("INSERT INTO album (id_artist, title) VALUES ((SELECT id FROM artist WHERE name='" + artistName + "'),'" + albumName + "');");
    db.close();
}


void CollectionDatabase::addMusic(Music *music) {
    QString artist = music->getArtist();
    QString album = music->getAlbum();
    QString title = music->getTitle();
    QString path = music->getFileUrl().path();
    unsigned int trackNumber = music->getTrackNumber();

    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }


    // TODO: if not exists, add artist
    // TODO: if not exists, add album


    db.exec("INSERT INTO music (id_album, track_number, title, path) VALUES ("
            "(SELECT id FROM album WHERE title='" + album + "' AND id_artist = (SELECT id FROM artist WHERE name = '" + artist +"')),"
            "" + QString::number(trackNumber) + ", \"" + title + "\", \"" + path + "\");"
            );

    if (db.lastError().type() != QSqlError::NoError) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }

    db.close();

}
