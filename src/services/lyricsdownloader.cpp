#include "lyricsdownloader.h"

LyricsDownloader::LyricsDownloader(QObject *parent) :
    QObject(parent)
{
    QUrl url("http://lyrics.wikia.com/Taylor_Swift:Mine");
    page.mainFrame()->load(url);

    connect(&page, SIGNAL(loadFinished(bool)), this, SLOT(render()));
}

// FIXME: why is this emitting the signal twice?
void LyricsDownloader::render() {
    QWebElement document = page.mainFrame()->documentElement();

    // TODO: remove mobile ringtone ad
    QWebElement lyricsDiv = document.findFirst("div.lyricbox");

    qDebug("Emitting lyrics!");
    emit lyricsReady(lyricsDiv);
}
