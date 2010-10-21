#include "lyricsdownloader.h"

LyricsDownloader::LyricsDownloader(QObject *parent) :
    QObject(parent)
{
    netManager = new QNetworkAccessManager(this);
}

void LyricsDownloader::getLyrics(QString artist, QString song) {
    QUrl url("http://lyrics.wikia.com/api.php");
    url.addQueryItem("func", "getSong");
    url.addQueryItem("artist", artist.toUtf8());
    url.addQueryItem("song", song.toUtf8());
    url.addQueryItem("fmt", "xml");

    QNetworkRequest netRequest;
    netRequest.setUrl(url);
    contextReply = netManager->get(netRequest);
    connect(contextReply, SIGNAL(finished()), this, SLOT(readContextReply()));
    connect(contextReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(lyricsError())); // TODO: specify which error was given
}

void LyricsDownloader::readContextReply() {
    QString replyString = QString::fromUtf8(contextReply->readAll());

    if (replyString.isEmpty()) {
        emit lyricsError();
        return; // Avoid empty parsing of XML
    }

    QString status;
    QXmlQuery query;
    query.setFocus(replyString);
    query.setQuery("LyricsResult/lyrics/text()");
    query.evaluateTo(&status);
    status = status.trimmed();

    /*
     * If we got the data successfully, let's read it.
     * I hate XML.
     */
    if (status.toLower() != "not found") {
        QString url;
        query.setQuery("LyricsResult/url/text()");
        query.evaluateTo(&url);
        url = url.trimmed();

        // Try to fetch lyrics
        fetchLyrics(url);
    }
    else {
        emit lyricsError();
    }
}

void LyricsDownloader::fetchLyrics(QUrl url) {
    page.mainFrame()->load(url);
    connect(&page, SIGNAL(loadFinished(bool)), this, SLOT(render()));
}


// FIXME: why is this emitting the signal twice?
void LyricsDownloader::render() {
    QWebElement document = page.mainFrame()->documentElement();
    // TODO: remove mobile ringtone ad
    QWebElement lyricsDiv = document.findFirst("div.lyricbox");

    emit lyricsReady(lyricsDiv);
}
