#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QMap>
#include <QUrl>
#include <phonon/MediaSource>
#include <phonon/MediaObject>
#include <phonon/AudioOutput>

class PlaylistItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

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

    Phonon::MediaObject *mediaObject;

    QString artist;
    QString title;
    QString album;
    QString duration;

private slots:
    void loadMetaData();

};

#endif // PLAYLISTITEM_H
