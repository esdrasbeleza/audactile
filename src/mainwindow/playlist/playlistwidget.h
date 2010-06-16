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
    void dndActionChanged(Qt::DropAction newAction);

signals:
    void songInformationUpdated(QString newSongInformation);


public:
    PlaylistWidget(QWidget *parent, Phonon::MediaObject *mediaObject);
    Phonon::MediaObject *mainMediaObject;
    int addSong(PlaylistItem *newItem, int index = -1);
    int addSong(QUrl url, int index = -1);


private:
    PlaylistItem *currentSong;
    PlaylistItem *nextSong;
    QDrag *drag;
    Qt::DropAction dndAction;
    void emitSongInformationUpdated();

    // Drag and drop events
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    Qt::DropActions supportedDropActions() const;
    void dragMoveEvent(QDragMoveEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // PLAYLISTWIDGET_H
