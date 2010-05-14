#include "playlistitem.h"

PlaylistItem::PlaylistItem(QString _filePath)
{
    filePath = _filePath;
    taglibFileRef =  FileRef(filePath.toAscii());

    // Set tags using taglib
    artist = QString(taglibFileRef.tag()->artist().toCString(true));
    album  = QString(taglibFileRef.tag()->album().toCString(true));
    title  = QString(taglibFileRef.tag()->title().toCString(true));

    if (artist.isEmpty()) artist = "Undefined";
    if (album.isEmpty())  album  = "Undefined";
    if (title.isEmpty())  title  = "Undefined";

    setText(0, title);
    setText(1, album);
    setText(2, artist);

    // TODO: use phonon to get duration.
}
