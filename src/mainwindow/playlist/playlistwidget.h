#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QTreeWidget>
#include <QHeaderView>
#include <phonon/MediaObject>
#include "playlistitem.h"

class PlaylistWidget : public QTreeWidget
{
    Q_OBJECT

private slots:
    void playSong(QModelIndex index);
    void enqueueNextSong();
    void removeBold();
    void fileChanged();

public:
    PlaylistWidget(QWidget *parent, Phonon::MediaObject *mediaObject);
    Phonon::MediaObject *mainMediaObject;

private:
    PlaylistItem* currentSong;
    PlaylistItem* nextSong;
};

#endif // PLAYLISTWIDGET_H
