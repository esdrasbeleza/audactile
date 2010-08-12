#include "lyricswidget.h"

LyricsWidget::LyricsWidget(QWidget *parent) : AbstractContainer(parent)
{
    setHtml("No music being listened!");

    // Try to fetch lyrics
    lyricsProvider = new LyricsDownloader();
    connect(lyricsProvider, SIGNAL(lyricsReady(QWebElement)), this, SLOT(showLyrics(QWebElement)));

}

void LyricsWidget::songInformationUpdated(QMap<QString, QString> newContextInformation) {
    lastRequest = newContextInformation;
    QString html("<div class=\"title\">" + newContextInformation.value("artist") + " - " + newContextInformation.value("title") +  "</div>");
    setHtml(html);
    lyricsProvider->getLyrics(newContextInformation.value("artist"), newContextInformation.value("title"));
}


void LyricsWidget::showLyrics(QWebElement webElement) {
    qDebug("Trying to show lyrics...");
    QString html("<div class=\"title\">" + lastRequest.value("artist") + " - " + lastRequest.value("title") +  "</div>");
    setHtml(html + "<p>" + webElement.toOuterXml() + "</p>");

    // Code to try to remove some tags
    //    QString code = "$('object').remove()";
    //    view->page()->mainFrame()->evaluateJavaScript(code);
}
