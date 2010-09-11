#include "music.h"


/*
 * TODO:
 * - Watch file for changes. If it's changed, update playlist.
 */
Music::Music(QString artist, QString album, QString title, QString path, unsigned int trackNumber) {
    this->artist = artist;
    this->album = album;
    this->title = title;
    this->fileUrl = QUrl(path);
    this->trackNumber = trackNumber;
}

Music::Music(QUrl fileUrl)
    {
    this->fileUrl = fileUrl;
    readMetaData();
}

void Music::readMetaData() {
    TagLib::FileRef taglibFileRef = TagLib::FileRef(fileUrl.toLocalFile().toUtf8());

    // Verify if some file is valid
    if (!taglibFileRef.isNull()) {
        trackNumber = taglibFileRef.tag()->track();

        // Read metadata
        artist = QString(taglibFileRef.tag()->artist().toCString()).toAscii();
        album = QString(taglibFileRef.tag()->album().toCString()).toAscii();
        title = QString(taglibFileRef.tag()->title().toCString()).toAscii();
        duration = taglibFileRef.audioProperties()->length();

        if (artist.isEmpty()) artist = "Undefined";
        if (album.isEmpty())  album  = "Undefined";
        if (title.isEmpty())  title  = "Undefined";

        qDebug("Valid!");
        valid = true;
    }
    else {
        qDebug("Invalid!");
        valid = false;
        // TODO: throw some exception
    }
}

bool Music::isValid() {
    return valid;
}

QString Music::getAlbum() {
    return album;
}

QString Music::getArtist() {
    return artist;
}

unsigned int Music::getDuration() {
    return duration;
}

QString Music::getTitle() {
    return title;
}

unsigned int Music::getTrackNumber() {
    return trackNumber;
}

QUrl Music::getFileUrl() {
    return fileUrl;
}
