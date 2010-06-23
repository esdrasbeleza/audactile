#include "playlistitem.h"

// TODO: if path is invalid, show error


PlaylistItem::PlaylistItem(QString itemFilePath)
{
    // TODO: make this use the another constructor.
    fileUrl = QUrl().fromLocalFile(itemFilePath);
    mediaObject = new Phonon::MediaObject(this);
    connect(this->mediaObject, SIGNAL(metaDataChanged()), this, SLOT(loadMetaData()));
    mediaObject->enqueue(fileUrl);
}

PlaylistItem::PlaylistItem(QUrl url) {
    fileUrl = url;
    mediaObject = new Phonon::MediaObject(this);
    connect(this->mediaObject, SIGNAL(metaDataChanged()), this, SLOT(loadMetaData()));
    mediaObject->enqueue(fileUrl);
}

void PlaylistItem::loadMetaData() {
    qDebug("loadMetaData");

    QMap<QString, QString> metaData = mediaObject->metaData();
    artist = metaData.value("ARTIST");
    album = metaData.value("ALBUM");
    title = metaData.value("TITLE");

    // TODO: put duration into right format
    // TODO: if duration = -1, emit invalid file!
    duration = QString::number(mediaObject->totalTime());

    if (artist.isEmpty()) artist = "Undefined";
    if (album.isEmpty())  album  = "Undefined";
    if (title.isEmpty())  title  = "Undefined";

    setText(0, title);
    setText(1, album);
    setText(2, artist);
    setText(3, duration);

    mediaObject->clear();
}


QUrl PlaylistItem::getFileUrl() {
    return fileUrl;
}

QString PlaylistItem::getArtist() {
    return artist;
}

QString PlaylistItem::getSongInfo() {
    return artist + " - " + title;
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

