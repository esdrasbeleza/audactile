#include "lastfmscrobbler.h"

LastFmScrobbler::LastFmScrobbler(Phonon::MediaObject *mediaObject)
{
    resetSongStatus();
    this->mediaObject = mediaObject;
    songsToScrobble = new QQueue<SongInfo>();
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(handleStateChange(Phonon::State,Phonon::State)));

    // TODO: call this only if Last.fm is enabled.
    // Maybe do a function to call this, calling only
    // on applicaton start or when Last.fm is enabled.
    state = this->LastFmStateNone;
    netManager = new QNetworkAccessManager(this);
    tryToLogin();
}


void LastFmScrobbler::tryToLogin() {
    QDateTime time = QDateTime::currentDateTime();
    QString timeStamp = QString::number(time.toTime_t());

    QUrl url("http://post.audioscrobbler.com/");
    url.addQueryItem("hs", "true");
    url.addQueryItem("p", "1.2.1");
    url.addQueryItem("c", "tst"); // TODO: change this to application name
    url.addQueryItem("v", "1.0");
    url.addQueryItem("u", LastFmSettings::username());
    url.addQueryItem("t", timeStamp);
    url.addQueryItem("a", generateToken(LastFmSettings::password(), timeStamp));

    state = LastFmStateWaitingToken;
    QNetworkRequest netRequest;
    netRequest.setUrl(url);
    qDebug("Asking to login to Last.fm...");
    authReply = netManager->get(netRequest);
    connect(authReply, SIGNAL(readyRead()), this, SLOT(readAuthenticationReply()));

}

void LastFmScrobbler::readAuthenticationReply() {
    qDebug("Got reply!");
    QString replyString = authReply->readAll();
    if (state == LastFmStateWaitingToken) {
        QStringList lines = replyString.split('\n');
        qDebug("Last.fm answer: " + QString(lines.at(0)).toUtf8());
        if (lines.at(0) == "OK") {
            state = LastFmGotToken;
            sessionId = lines.at(1);
            nowPlaying = lines.at(2);
            submission = lines.at(3);
            qDebug("Last.fm token: " + sessionId.toUtf8());
        }
        // TODO: better feedback for the user of what's wrong.
        // BANNED / BADAUTH / BADTIME / FAILED <reason>
        else {
            qDebug("Authentication problem! Disabling Last.fm");
            LastFmSettings::setActive(false);
        }
    }
}


void LastFmScrobbler::readNowPlayingReply() {
    qDebug("Got Now Playing reply!");
    QString replyString = nowPlayingReply->readAll();
    qDebug("Reply: " + replyString.toUtf8());
}


QString LastFmScrobbler::generateToken(QString input, QString timestamp) {
    /*
     * As said in http://www.last.fm/api/submissions#1.2 ,
     * we must create a token in the format
     * token = md5(md5(password) + timestamp)
     * to use in scrobble.
     */
    QByteArray encryptedPassword = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Md5).toHex();
    QByteArray token = QCryptographicHash::hash(encryptedPassword + timestamp.toUtf8(), QCryptographicHash::Md5).toHex();
    return QString(token);
}

void LastFmScrobbler::onTick(qint64 time) {
    /*
     *
     * If Last.fm was disabled, the signal will be disconnected only
     * when the Phonon state changes. This test avoid undesired
     * scrobbling.
     */
    if (!LastFmSettings::isActive()) return;

    ellapsedTime = mediaObject->currentTime();
    /*
     * We only can scrobble songs that were played for more than
     * 240s or half of its length.
     */
    if (ellapsedTime >= mediaObject->remainingTime() || ellapsedTime >= 240000) {
        enqueueTrack();
        tryToScrobbleQueue();

        // Disconnect this slot if the song was already queued.
        disconnect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(onTick(qint64)));
    }
}

void LastFmScrobbler::resetSongStatus() {
    ellapsedTime = 0;
    canScrobble = false;
    SongInfo currentSong;
}

void LastFmScrobbler::enqueueTrack() {
    qDebug("Song queued to scrobble!");
    songsToScrobble->enqueue(currentSong);
}

void LastFmScrobbler::tryToScrobbleQueue() {
    qDebug("Trying to scrobble queued songs");
}

void LastFmScrobbler::handleStateChange(Phonon::State newState, Phonon::State oldState) {
    // Disconnect slots if Last.fm is disabled.
    if (!LastFmSettings::isActive()) {
        qDebug("Last.fm is disabled");
        disconnect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(onTick(qint64)));
        disconnect(mediaObject, SIGNAL(finished()), this, SLOT(resetSongStatus()));
        return;
    }


    // Save information to scrobble!
    if (newState == Phonon::PlayingState && (oldState == Phonon::StoppedState || oldState == Phonon::LoadingState)) {
        QMap<QString, QString> metaData = mediaObject->metaData();
        QString artist = metaData.value("ARTIST");
        QString album = metaData.value("ALBUM");
        QString title = metaData.value("TITLE");

        // We only can scrobble titles that have
        // artist and title defined.
        if (!artist.isEmpty() && !title.isEmpty() && state == LastFmGotToken && mediaObject->totalTime() >= 30000) {
            timeToScrobble = qRound(mediaObject->totalTime() / 2000);
            qDebug("Last.fm is enabled!");
            connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(onTick(qint64)));
            connect(mediaObject, SIGNAL(finished()), this, SLOT(resetSongStatus()));

            canScrobble = true;
            qDebug("Can scrobble!");

            SongInfo currentSong;
            currentSong.artist = artist;
            currentSong.title = title;
            if (!album.isEmpty()) currentSong.album = album;

            QDateTime time = QDateTime::currentDateTime();
            currentSong.startTimeStamp = QString::number(time.toTime_t()).toUtf8();

            // Send a "Now Playing" notification to Last.fm
            QUrl url(nowPlaying);
            QString dataToPost = "s=" + sessionId + "&" +
                                 "a=" + artist + "&" +
                                 "t=" + title + "&" +
                                 "b=" + album + "&" +
                                 "l=" + QString::number(qRound(mediaObject->totalTime() / 1000)) + "&" +
                                 "n=";

            QNetworkRequest netRequest;
            netRequest.setUrl(url);
            qDebug("Sending Now Playing...");
            nowPlayingReply = netManager->post(netRequest,dataToPost.toUtf8());
            connect(nowPlayingReply, SIGNAL(readyRead()), this, SLOT(readNowPlayingReply()));

        }
    }
    else if (newState == Phonon::StoppedState) {
        resetSongStatus();
    }

}

