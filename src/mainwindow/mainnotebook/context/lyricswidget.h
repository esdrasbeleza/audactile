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
    void songInformationUpdated(QMap<QString, QString> newContextInformation);
    void resetLabels();

private:
    LyricsDownloader *lyricsProvider;
    QMap<QString, QString> lastRequest;

private slots:
    void showLyrics(QWebElement webElement);

};

#endif // LYRICSWIDGET_H
