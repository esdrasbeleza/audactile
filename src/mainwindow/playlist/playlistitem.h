#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QTreeWidgetItem>
#include <QUrl>
#include <taglib/tag.h>
#include <taglib/fileref.h>


class PlaylistItem : public QTreeWidgetItem
{

public:
    PlaylistItem(QString);
    PlaylistItem(QUrl url);
    bool isValid();
    QUrl getFileUrl();
    QString getArtist();
    QString getTitle();
    unsigned int getTrackNumber();
    void setBold();
    void removeBold();
    QString getSongInfo();
    unsigned int getDuration();
    int index; // Index where item must be inserted at PlaylistWidget


private:
    void loadFile();
    QUrl fileUrl;
    unsigned int trackNumber;
    QString artist;
    QString title;
    QString album;
    unsigned int duration;
    bool valid;


};

#endif // PLAYLISTITEM_H
