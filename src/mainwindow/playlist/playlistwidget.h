#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QTreeWidget>
#include <QHeaderView>
#include <QDropEvent>
#include <QUrl>
#include <QFileInfo>
#include <phonon/MediaObject>
#include "playlistitem.h"

class PlaylistWidget : public QTreeWidget
{
    Q_OBJECT

private slots:
    void playSong(QModelIndex index);
    void handleStateChange(Phonon::State newState);
    void enqueueNextSong();
    void removeBold();
    void fileChanged();
    void playNextSong();
    void playPreviousSong();

signals:
    void songInformationUpdated(QString newSongInformation);


public:
    PlaylistWidget(QWidget *parent, Phonon::MediaObject *mediaObject);
    Phonon::MediaObject *mainMediaObject;
    void addSong(PlaylistItem *newItem);
    void addSong(QString filePath);


private:
    PlaylistItem* currentSong;
    PlaylistItem* nextSong;
    void emitSongInformationUpdated();

    // Drag and drop events
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

};

#endif // PLAYLISTWIDGET_H
