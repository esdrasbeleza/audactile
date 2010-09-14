#include "playlistitem.h"

// TODO: if path is invalid, show error


PlaylistItem::PlaylistItem(QString itemFilePath)
{
    fileUrl = QUrl().fromLocalFile(itemFilePath);
    loadFile();
}

PlaylistItem::PlaylistItem(QUrl url) {
    fileUrl = url;
    loadFile();
}

void PlaylistItem::loadFile() {
    music = new Music(fileUrl);

    if (music->getTrackNumber() > 0) { setData(0, Qt::DisplayRole, music->getTrackNumber()); }
    else { setData(0, Qt::DisplayRole, QString("")); }

    QString qStr;
    int duration = music->getDuration();
    int secs = duration % 60;
    int mins = duration / 60;

    setText(1, music->getTitle());
    setText(2, music->getAlbum());
    setText(3, music->getArtist());
    setText(4, QString::number(mins) + ":" + qStr.sprintf("%02d", secs));
 }


Music * PlaylistItem::getMusic() {
    return music;
}

bool PlaylistItem::isValid() {
    if (music != NULL) {
       return music->isValid();
    }
    else {
        return false;
    }
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
