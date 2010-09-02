#include "collectiondatabase.h"


/*
 * TODO:
 * - Handle errors
 * - Improve indexes
 * - Use some mechanism to speed up the process to add multiple songs of the same artist
 *
 */

CollectionDatabase::CollectionDatabase(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString database = QDesktopServices::storageLocation(QDesktopServices::DataLocation) + QDir::separator() + "collection.db";
    qDebug("DATABASE: " + database.toUtf8());
    db.setDatabaseName(database);

    createDatabase();

    artistModel = new QSqlRelationalTableModel(this);
    artistModel->setTable("artist");
    artistModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    albumModel = new QSqlRelationalTableModel(this);
    albumModel->setTable("album");
    albumModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    albumModel->setRelation(albumModel->fieldIndex("id_artist"), QSqlRelation("artist", "id", "artist_name"));

    musicModel = new QSqlRelationalTableModel(this);
    musicModel->setTable("music");
    musicModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    musicModel->setRelation(musicModel->fieldIndex("id_album"), QSqlRelation("album", "id", "album_title"));

}


void CollectionDatabase::createDatabase() {
    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }

    QStringList tables = db.tables(QSql::Tables);
    QStringList views = db.tables(QSql::Views);

    // TODO: use titles as primary key?

    if (!tables.contains("artist")) {
        db.exec("CREATE TABLE artist ("
                "id integer primary key AUTOINCREMENT, "
                "name varchar(120) UNIQUE NOT NULL"
                ");");
    }

    if (!tables.contains("album")) {
        db.exec("CREATE TABLE album ("
                "id integer primary key AUTOINCREMENT, "
                "id_artist int, "
                "title varchar(120) NOT NULL"
                ");");
    }

    if (!tables.contains("music")) {
        db.exec("CREATE TABLE music ("
                "id integer primary key AUTOINCREMENT, "
                "id_album int, "
                "track_number int, "
                "title varchar(120) NOT NULL,"
                "path varchar(2048) UNIQUE NOT NULL"
                ");");
    }

    if (!views.contains("collection")) {
        db.exec("CREATE VIEW collection AS "
                "SELECT artist.name, album.title, music.title, music.track_number, music.path"
                "FROM artist, album, music"
                "WHERE album.id_artist = artist.id AND music.id_album = album.id"
                "ORDER BY artist.name, album.title, music.track_number");
    }

    if (db.lastError().type() != QSqlError::NoError) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }


}

void CollectionDatabase::addArtist(QString artistName) {
    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }

    QSqlQuery query;
    query.exec("SELECT count('name') FROM artist WHERE name='" + artistName + "';");
    if (query.first()) {
        int total = query.value(0).toInt();
        qDebug("Artist Total: " + QString::number(total).toUtf8());
        if (total == 0) db.exec("INSERT INTO artist (name) VALUES ('" + artistName + "');");
    }

    qDebug("addArtist end");
}

void CollectionDatabase::addAlbum(QString artistName, QString albumName) {
    // Since addArtist tests if artist already exists, it's safe to call it here
    qDebug("addAlbum");

    addArtist(artistName);

    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }

    QSqlQuery query;
    query.exec("SELECT count('title') FROM album WHERE title='" + albumName + "' AND id_artist=(SELECT id FROM artist WHERE name='" + artistName + "');");
    if (query.first()) {
        int total = query.value(0).toInt();
        qDebug("Album Total: " + QString::number(total).toUtf8());
        if (total == 0) db.exec("INSERT INTO album (id_artist, title) VALUES ((SELECT id FROM artist WHERE name='" + artistName + "'),'" + albumName + "');");
    }
    query.clear();

    if (db.lastError().type() != QSqlError::NoError) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }

    qDebug("addAlbum end");
}


void CollectionDatabase::addMusic(QString path) {
    Music *music = new Music(QUrl::fromLocalFile(path));
    addMusic(music);
}

void CollectionDatabase::addMusic(Music *music) {
    QString artist = music->getArtist();
    QString album = music->getAlbum();
    QString title = music->getTitle();
    QString path = music->getFileUrl().path();
    unsigned int trackNumber = music->getTrackNumber();

    qDebug("addMusic");

    /*
     * Assert that artist and album exists.
     * addAlbum() asserts artist existence.
     *
     */
    addAlbum(artist, album);

    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }

    QSqlQuery query;
    query.exec("SELECT * FROM music WHERE path='" + path + "'");
    if (!query.first()) {
        qDebug("Inserting music!");
        db.exec("INSERT INTO music (id_album, track_number, title, path) VALUES ("
                "(SELECT id FROM album WHERE title='" + album + "' AND id_artist = (SELECT id FROM artist WHERE name = '" + artist +"')),"
                "" + QString::number(trackNumber) + ", \"" + title + "\", \"" + path + "\");"
                );

    }

    if (db.lastError().type() != QSqlError::NoError) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }

    qDebug("addMusic end");
}


void CollectionDatabase::removeArtist(QString artistName) {
    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }
    db.exec("DELETE FROM artist WHERE name='" + artistName + "'");
}

void CollectionDatabase::removeAlbum(QString artistName, QString albumName) {
    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }
    db.exec("DELETE FROM album WHERE name='" + artistName + "' AND id_artist=(SELECT id FROM artist WHERE name='" + artistName + "')");
}

void CollectionDatabase::removeMusic(QString path) {
    if (!db.open()) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }
    db.exec("DELETE FROM music WHERE path='" + path + "'");
}

void CollectionDatabase::removeMusic(Music *music) {
    removeMusic(music->getFileUrl().path());
}
