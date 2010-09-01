#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QTreeWidgetItem>
#include <QUrl>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include "../../music.h"


class PlaylistItem : public QTreeWidgetItem
{

public:
    PlaylistItem(QString);
    PlaylistItem(QUrl url);
    Music * getMusic();
    bool isValid();
    void setBold();
    void removeBold();
    int index; // Index where item must be inserted at PlaylistWidget


private:
    QUrl fileUrl;
    Music *music;
    void loadFile();
};

#endif // PLAYLISTITEM_H
