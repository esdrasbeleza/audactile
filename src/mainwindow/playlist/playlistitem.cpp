#include "playlistitem.h"

// TODO: if path is invalid, show error


PlaylistItem::PlaylistItem(QString itemFilePath)
{
    qDebug("PlaylistItem by path");

    // TODO: make this use the another constructor.
    fileUrl = QUrl().fromLocalFile(itemFilePath);
    mediaObject = new Phonon::MediaObject(this);
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(loadMetaData(Phonon::State,Phonon::State)));
    mediaObject->setCurrentSource(fileUrl);
}

PlaylistItem::PlaylistItem(QUrl url) {
    qDebug("PlaylistItem by URL");
    fileUrl = url;
    qDebug("URL: " + url.path().toUtf8());

    mediaObject = new Phonon::MediaObject(this);
    connect(this->mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(loadMetaData(Phonon::State,Phonon::State)));
    mediaObject->setCurrentSource(fileUrl);
}

void PlaylistItem::loadMetaData(Phonon::State newState, Phonon::State) {
    qDebug("loadMetaData");

    if (newState == Phonon::ErrorState) {
        qDebug("Error!");
        return;
    }

    if (mediaObject->currentSource().type() == Phonon::MediaSource::Invalid) {
        qDebug("Error!");
        return;
    }
    // If duration is greater than -1, it's a valid file
    duration = mediaObject->totalTime();
    if (duration > -1) {
        QMap<QString, QString> metaData = mediaObject->metaData();
        artist = metaData.value("ARTIST");
        album = metaData.value("ALBUM");
        title = metaData.value("TITLE");

        if (artist.isEmpty()) artist = "Undefined";
        if (album.isEmpty())  album  = "Undefined";
        if (title.isEmpty())  title  = "Undefined";

        setText(0, title);
        setText(1, album);
        setText(2, artist);

        QString qStr;
        int secs = (duration / 1000) % 60;
        int mins = (duration / 1000) / 60;
        setText(3, QString::number(mins) + ":" + qStr.sprintf("%02d", secs));
        emit validFile(this);
    }
    else {
        emit invalidFile(this);
    }
}

qint64 PlaylistItem::getDuration() {
    return duration;
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

