#ifndef LYRICSDOWNLOADER_H
#define LYRICSDOWNLOADER_H

#include <QObject>
#include <QUrl>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>

class LyricsDownloader : public QObject
{
Q_OBJECT
public:
    explicit LyricsDownloader(QObject *parent = 0);

private:
    QWebPage page;

signals:
    void lyricsReady(QWebElement);

public slots:
    void render();

};

#endif // LYRICSDOWNLOADER_H
