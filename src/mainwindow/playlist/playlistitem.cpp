#include "playlistitem.h"

// TODO: if path is invalid, show error


PlaylistItem::PlaylistItem(QString itemFilePath)
{
    qDebug("PlaylistItem by path");
    fileUrl = QUrl().fromLocalFile(itemFilePath);
    loadFile();
}

PlaylistItem::PlaylistItem(QUrl url) {
    qDebug("PlaylistItem by URL");
    fileUrl = url;
    loadFile();
}

void PlaylistItem::loadFile() {
    qDebug("File: " + fileUrl.toLocalFile().toUtf8());
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


        QString qStr;
        int secs = duration % 60;
        int mins = duration / 60;

        // Set columns text
        if (trackNumber > 0) { setData(0, Qt::DisplayRole, trackNumber); }
        else { setData(0, Qt::DisplayRole, QString("")); }
        setText(1, title);
        setText(2, album);
        setText(3, artist);
        setText(4, QString::number(mins) + ":" + qStr.sprintf("%02d", secs));

        qDebug("Valid!");
        valid = true;
    }
    else {
        qDebug("Invalid!");
        valid = false;
    }
}

unsigned int PlaylistItem::getDuration() {
    return duration;
}

bool PlaylistItem::isValid() {
    return valid;
}

QUrl PlaylistItem::getFileUrl() {
    qDebug("getFileUrl");
    return fileUrl;
}

QString PlaylistItem::getArtist() {
    return artist;
}

QString PlaylistItem::getTitle() {
    return title;
}

unsigned int PlaylistItem::getTrackNumber() {
    return trackNumber;
}

void PlaylistItem::setBold() {
    for (int i = 0; i < columnCount(); i++) {
        QFont itemFont = font(i);
        itemFont.setBold(true);
        setFont(i, itemFont);
    }
}

void PlaylistItem::removeBold() {
    for (int i = 0; i < columnCount(); i++) {
        QFont itemFont = font(i);
        itemFont.setBold(false);
        setFont(i, itemFont);
    }
}

