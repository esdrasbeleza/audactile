#ifndef LASTFMSCROBBLER_H
#define LASTFMSCROBBLER_H

// TODO: change this file location
#include <QObject>
#include <QCryptographicHash> // To generate the token.
#include <QDateTime>
#include <QStringList>
#include <QList>
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
    void readSubmissionReply();

private:
    void handshake();
    void tryToScrobble();
    QString generateToken(QString input, QString timestamp);
    Phonon::MediaObject *mediaObject;
    int ellapsedTime;
    bool canScrobble;
    struct SongInfo {
        QString artist;
        QString album;
        QString title;
        QString startTimeStamp;
        QString duration;
    };
    SongInfo currentSong;
    QList<SongInfo> *songsToScrobble;

    // Network related stuff
    enum LastFmState  {
        LastFmStateNone = 0,
        LastFmStateWaitingToken = 1,
        LastFmGotToken = 2
    };
    LastFmState state;
    int timeToScrobble;
    qint64 lastTickTime;
    QString sessionId;
    QString nowPlayingUrl;
    QString submissionUrl;
    QNetworkAccessManager *netManager;
    QNetworkRequest *netRequest;
    QNetworkReply *authReply;
    QNetworkReply *nowPlayingReply;
    QNetworkReply *submissionReply;



};

#endif // LASTFMSCROBBLER_H
