#ifndef LYRICSDOWNLOADER_H
#define LYRICSDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QXmlQuery>
#include <QNetworkReply>

class LyricsDownloader : public QObject
{
Q_OBJECT
public:
    explicit LyricsDownloader(QObject *parent = 0);
    void getLyrics(QString artist, QString song);

private:
    QWebPage page;
    QNetworkAccessManager *netManager;
    QNetworkReply *contextReply;

signals:
    void lyricsReady(QWebElement);
    void lyricsError();

public slots:
    void fetchLyrics(QUrl);
    void render();
    void readContextReply();

};

#endif // LYRICSDOWNLOADER_H
