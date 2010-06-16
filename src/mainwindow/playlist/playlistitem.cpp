#include "playlistitem.h"

PlaylistItem::PlaylistItem(QString itemFilePath)
{
    filePath = itemFilePath;
    fileUrl = QUrl().fromLocalFile(filePath);

    // Set tags using taglib
    taglibFileRef =  TagLib::FileRef(filePath.toUtf8());
    artist = QString(taglibFileRef.tag()->artist().toCString());
    album  = QString(taglibFileRef.tag()->album().toCString());
    title  = QString(taglibFileRef.tag()->title().toCString());

    if (artist.isEmpty()) artist = "Undefined";
    if (album.isEmpty())  album  = "Undefined";
    if (title.isEmpty())  title  = "Undefined";


    setText(0, title);
    setText(1, album);
    setText(2, artist);


    // TODO: use phonon to get duration.
}

PlaylistItem::PlaylistItem(QUrl url) {
    filePath = QFileInfo(url.path()).canonicalFilePath();
    fileUrl = url;

    // If the path is null, return
    // TODO: show some error message
    if (filePath.size() == 0) return;


    // Set tags using taglib
    taglibFileRef =  TagLib::FileRef(filePath.toUtf8());
    artist = QString(taglibFileRef.tag()->artist().toCString());
    album  = QString(taglibFileRef.tag()->album().toCString());
    title  = QString(taglibFileRef.tag()->title().toCString());

    if (artist.isEmpty()) artist = "Undefined";
    if (album.isEmpty())  album  = "Undefined";
    if (title.isEmpty())  title  = "Undefined";


    setText(0, title);
    setText(1, album);
    setText(2, artist);
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

