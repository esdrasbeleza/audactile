#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QTreeWidgetItem>
#include <taglib/tag.h>
#include <taglib/fileref.h>

using namespace TagLib;

class PlaylistItem : public QTreeWidgetItem
{
public:
    PlaylistItem(QString);

private:
    QString filePath;
    QString artist;
    QString title;
    QString album;
    QString duration;

    FileRef taglibFileRef;
};

#endif // PLAYLISTITEM_H
