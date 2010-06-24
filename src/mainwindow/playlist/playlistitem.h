#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QTreeWidgetItem>
#include <QMessageBox>
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
    qint64 getDuration();


private:
    QUrl fileUrl;

    Phonon::MediaObject *mediaObject;

    QString artist;
    QString title;
    QString album;
    qint64 duration;

private slots:
    void loadMetaData(Phonon::State newState, Phonon::State);


};

#endif // PLAYLISTITEM_H
