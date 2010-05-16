#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QTreeWidgetItem>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <phonon/MediaSource>


class PlaylistItem : public QTreeWidgetItem
{

public:
    PlaylistItem(QString);
    QString getFilePath();
    QString getArtist();
    void setBold();
    void removeBold();
    QString getSongInfo();


private:
    QString filePath;
    QString artist;
    QString title;
    QString album;
    QString duration;

    // TagLib references
    TagLib::FileRef taglibFileRef;


};

#endif // PLAYLISTITEM_H
