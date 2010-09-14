#include "collectiondatabase.h"


/*
 * TODO:
 * - When some music is removed, verify if the album must exist
 * - When some album is removed, verify if the artist must exist
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
    db.setDatabaseName(database);

    createDatabase();
}

QSqlTableModel *CollectionDatabase::collectionModel() {
    QSqlTableModel *model = new QSqlTableModel();
    model->setTable("collection");
    model->setSort(model->fieldIndex("artist"), Qt::AscendingOrder);
    model->setSort(model->fieldIndex("album"), Qt::AscendingOrder); // TODO: sort by year
    model->setSort(model->fieldIndex("track_number"), Qt::AscendingOrder);
    model->select();
    return model;
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
                "path varchar(2048) UNIQUE NOT NULL, "
                "last_modified int "
                ");");
    }

    if (!views.contains("collection")) {
        db.exec("CREATE VIEW collection AS "
                "SELECT artist.name as artist, album.title as album, music.title as music, music.track_number as track_number, music.path as path "
                "FROM artist, album, music "
                "WHERE album.id_artist = artist.id AND music.id_album = album.id "
                "ORDER BY artist.name, album.title, music.track_number;");
    }

    if (db.lastError().type() != QSqlError::NoError) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }


}

void CollectionDatabase::addArtist(QString artistName) {
    if (!db.isOpen()) {
        if (!db.open()) qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT count('name') FROM artist WHERE name=:artist;");
    query.bindValue(":artist", artistName);
    query.exec();
    if (query.first()) {
        int total = query.value(0).toInt();
        if (total == 0) {
            QSqlQuery insertQuery(db);
            insertQuery.prepare("INSERT INTO artist (name) VALUES (:artist);");
            insertQuery.bindValue(":artist", artistName);
            insertQuery.exec();
        }
    }
}

void CollectionDatabase::addAlbum(QString artistName, QString albumName) {
    // Since addArtist tests if artist already exists, it's safe to call it here
    addArtist(artistName);

    if (!db.isOpen()) {
        if (!db.open()) qDebug("ERROR! " + db.lastError().text().toUtf8());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT count('title') FROM album WHERE title=:album AND id_artist=(SELECT id FROM artist WHERE name=:artist);");
    query.bindValue(":album", albumName);
    query.bindValue(":artist", artistName);
    query.exec();
    if (query.first()) {
        int total = query.value(0).toInt();
        if (total == 0) {
            QSqlQuery insertQuery(db);
            insertQuery.prepare("INSERT INTO album (id_artist, title) VALUES ((SELECT id FROM artist WHERE name=:artist),:album);");
            insertQuery.bindValue(":album", albumName);
            insertQuery.bindValue(":artist", artistName);
            insertQuery.exec();
        }
    }
    query.clear();

    if (db.lastError().type() != QSqlError::NoError) {
        qDebug("ERROR! " + db.lastError().text().toUtf8());
    }
}

bool CollectionDatabase::addOrUpdateMusic(Music *music) {
    if (!music->isValid()) return false;

    QString artist = music->getArtist();
    QString album = music->getAlbum();
    QString title = music->getTitle();
    QString path = music->getFileUrl().path();
    unsigned int trackNumber = music->getTrackNumber();
    unsigned int lastModified = QFileInfo(path).lastModified().toTime_t();

    if (!db.isOpen()) {
        if (!db.open()) qDebug("ERROR! " + db.lastError().text().toUtf8());
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT count(*) FROM music WHERE path=?");
    query.bindValue(":path", path);
    query.exec();
    query.first();
    unsigned int total = query.value(0).toUInt();
    if (total == 0) {
        /*
         * Assert that artist and album exists.
         * addAlbum() asserts artist existence.
         *
         */
        addAlbum(artist, album);

        QSqlQuery insertQuery(db);
        insertQuery.prepare(
                "INSERT INTO music (id_album, track_number, title, path, last_modified) VALUES ("
                "(SELECT id FROM album WHERE title=:album AND id_artist = (SELECT id FROM artist WHERE name = :artist)),"
                ":tracknumber, :title, :path, :lastmodified);"
                );
        insertQuery.bindValue(":album", album);
        insertQuery.bindValue(":artist", artist);
        insertQuery.bindValue(":tracknumber", trackNumber);
        insertQuery.bindValue(":title", title);
        insertQuery.bindValue(":path", path);
        insertQuery.bindValue(":lastmodified", lastModified);
        insertQuery.exec();

        if (db.lastError().type() != QSqlError::NoError) {
            qDebug("ERROR! " + db.lastError().text().toUtf8());
            qDebug(insertQuery.executedQuery().toUtf8());
            return false;
        }
        return true;

    }
    else {
        // If the file was updated, we must update the database.
        query.prepare("SELECT last_modified FROM music WHERE path=:path");
        query.bindValue(":path", path);
        query.exec();
        query.first();
        unsigned int lastModifiedInDb = query.value(0).toUInt();
        if (lastModified > lastModifiedInDb) {
            QSqlQuery updateQuery(db);
            updateQuery.prepare(
                    "UPDATE music SET "
                    "track_number = :tracknumber, "
                    "title = :title, "
                    "id_album = (SELECT id FROM album WHERE title=:album AND id_artist = (SELECT id FROM artist WHERE name = :artist)), "
                    "last_modified = :lastmodified "
                    "WHERE path = :path"
                    );
            updateQuery.bindValue(":album", album);
            updateQuery.bindValue(":artist", artist);
            updateQuery.bindValue(":tracknumber", trackNumber);
            updateQuery.bindValue(":title", title);
            updateQuery.bindValue(":path", path);
            updateQuery.bindValue(":lastmodified", lastModified);
            updateQuery.exec();

            if (db.lastError().type() != QSqlError::NoError) {
                qDebug("ERROR! " + db.lastError().text().toUtf8());
                qDebug(path.toUtf8());
                return false;
            }
            return true;
        }
    }
    return false;
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
    db.exec("DELETE FROM album WHERE name='" + albumName + "' AND id_artist=(SELECT id FROM artist WHERE name='" + artistName + "')");
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
