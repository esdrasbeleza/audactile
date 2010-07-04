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
    netReply = netManager->get(netRequest);
    connect(netReply, SIGNAL(readyRead()), this, SLOT(readReply()));

}

void LastFmScrobbler::readReply() {
    qDebug("Got reply!");
    QString replyArray = netReply->readAll();
    if (state == LastFmStateWaitingToken) {
        QStringList lines = replyArray.split('\n');
        if (lines.at(0) == "OK") {
            state = LastFmGotToken;
            token = lines.at(1);
        }
        break;
    }
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

    ellapsedTime++;
    qint64 totalTime = mediaObject->totalTime();
    if (totalTime == 0) return; // Avoid division by 0 below

    /*
     * We only can scrobble songs with more than 30s of duration,
     * and that were played for more than 240s or half of its length.
     */
    int percent = (int)(((double)time / (double)totalTime) * 100.0);
    if (totalTime >= 30000 && (percent >= 50 || ellapsedTime >= 240)) {
        enqueueTrack();
        tryToScrobbleQueue();
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
    // Let's verify if Last.fm is enabled.
    if (LastFmSettings::isActive()) {
        qDebug("Last.fm is enabled!");
        connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(onTick(qint64)));
        connect(mediaObject, SIGNAL(finished()), this, SLOT(resetSongStatus()));
    }
    // Disconnect slots if Last.fm is disabled.
    else {
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
        if (!artist.isEmpty() && !title.isEmpty()) {
            canScrobble = true;
            qDebug("Can scrobble!");

            SongInfo currentSong;
            currentSong.artist = artist;
            currentSong.title = title;
            if (!album.isEmpty()) currentSong.album = album;

            QDateTime time = QDateTime::currentDateTime();
            currentSong.startTimeStamp = QString::number(time.toTime_t()).toUtf8();
        }
    }
    else if (newState == Phonon::StoppedState) {
        resetSongStatus();
    }

}

