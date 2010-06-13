#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QUrl>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <phonon/MediaSource>


class PlaylistItem : public QTreeWidgetItem
{

public:
    PlaylistItem(QString);
    PlaylistItem(QUrl url);
    QUrl getFileUrl();
    QString getArtist();
    void setBold();
    void removeBold();
    QString getSongInfo();


private:
    QUrl fileUrl;
    QString filePath;
    QString artist;
    QString title;
    QString album;
    QString duration;

    // TagLib references
    TagLib::FileRef taglibFileRef;


};

#endif // PLAYLISTITEM_H
