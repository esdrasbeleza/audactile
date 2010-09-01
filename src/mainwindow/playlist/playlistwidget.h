#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QTreeWidget>
#include <QHeaderView>
#include <QDropEvent>
#include <QUrl>
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <phonon/MediaObject>
#include "playlistitem.h"
#include "../../music.h"

/*
 * TODO: make a PlaylistEngine, which will make the work of handle the current songs.
 *       PlaylistWidget will only make the work of handle the visualization.
 *
 */
class PlaylistWidget : public QTreeWidget
{
    Q_OBJECT

private slots:
    void playSong(QTreeWidgetItem *doubleClickedItem);
    void handleStateChange(Phonon::State newState);
    void enqueueNextSong();
    void removeBold();
    void fileChanged();
    void playNextSong();
    void playPreviousSong();
    void dndActionChanged(Qt::DropAction newAction);
    void insertValidItem(PlaylistItem *newItem);
    void deleteInvalidItem(PlaylistItem *invalidItem);
    void addSong(PlaylistItem *newItem, int index = -1);
    void addSong(QUrl url, int index = -1);

signals:
    void songInformationUpdated(QMap<QString, QString> newSongInformation);


public:
    PlaylistWidget(QWidget *parent, Phonon::MediaObject *mediaObject);


private:
    PlaylistItem *currentSong;
    PlaylistItem *nextSong;
    Phonon::MediaObject *mainMediaObject;
    QDrag *drag;
    Qt::DropAction dndAction;
    void emitSongInformationUpdated();
    void addFolder(QUrl url, int &index);


    // Drag and drop events
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    Qt::DropActions supportedDropActions() const;
    void dragMoveEvent(QDragMoveEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    // Keyboard events
    void keyPressEvent(QKeyEvent *event);
    void removeSelectedItems();
    void selectAll();

};

#endif // PLAYLISTWIDGET_H
