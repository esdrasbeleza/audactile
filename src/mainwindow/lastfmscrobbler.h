#ifndef LASTFMSCROBBLER_H
#define LASTFMSCROBBLER_H

#include <QObject>
#include <QCryptographicHash> // To generate the token.
#include <QDateTime>
#include <QStringList>
#include <QQueue>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
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
    void resetSongStatus();

    // Network related stuff
    void readAuthenticationReply();
    void readNowPlayingReply();

private:
    void tryToLogin();
    void enqueueTrack();
    void tryToScrobbleQueue();
    QString generateToken(QString input, QString timestamp);
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

    // Network related stuff
    enum LastFmState  {
        LastFmStateNone = 0,
        LastFmStateWaitingToken = 1,
        LastFmGotToken = 2
    };
    LastFmState state;
    QString sessionId;
    QString nowPlaying;
    QString submission;
    QNetworkAccessManager *netManager;
    QNetworkRequest *netRequest;
    QNetworkReply *authReply;
    QNetworkReply *nowPlayingReply;



};

#endif // LASTFMSCROBBLER_H
