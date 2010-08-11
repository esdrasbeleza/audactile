#include "lyricswidget.h"

LyricsWidget::LyricsWidget(QWidget *parent) : AbstractContainer(parent)
{
    setHtml("No music being listened!");

    // Try to fetch lyrics
    lyricsProvider = new LyricsDownloader();
    connect(lyricsProvider, SIGNAL(lyricsReady(QWebElement)), this, SLOT(showLyrics(QWebElement)));
}

void LyricsWidget::showLyrics(QWebElement webElement) {
    qDebug("Trying to show lyrics...");
    setHtml(webElement.toOuterXml());
}
