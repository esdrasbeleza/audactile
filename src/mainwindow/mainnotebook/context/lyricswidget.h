#ifndef LYRICSWIDGET_H
#define LYRICSWIDGET_H

#include <QWidget>
#include <QWebElement>
#include "abstractcontainer.h"
#include "../../../services/lyricsdownloader.h"

class LyricsWidget : public AbstractContainer
{
    Q_OBJECT

public:
    LyricsWidget(QWidget *parent);

private:
    LyricsDownloader *lyricsProvider;

private slots:
    void showLyrics(QWebElement webElement);

};

#endif // LYRICSWIDGET_H
