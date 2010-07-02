#ifndef LASTFMSCROBBLER_H
#define LASTFMSCROBBLER_H

#include <QObject>
#include <QCryptographicHash> // To generate the token.
#include <QDateTime>
#include <QQueue>
#include <phonon/MediaObject>
#include "../settings/lastfmsettings.h"

class LastFmScrobbler : QObject
{
Q_OBJECT

public:
    LastFmScrobbler(Phonon::MediaObject *mediaObject);

signals:

public slots:
    void onTick(qint64 time);
    void handleStateChange(Phonon::State, Phonon::State);
    void resetStatus();

private:
    void enqueueTrack();
    QString generateToken(QString input);
    Phonon::MediaObject *mediaObject;
    int ellapsedTime;
    bool canScrobble;
    struct SongInfo {
        QString artist;
        QString album;
        QString title;
        QString startTimeStamp;
    };
    SongInfo currentSong;
    QQueue<SongInfo> *songsToScrobble;

};

#endif // LASTFMSCROBBLER_H
