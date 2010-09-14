#ifndef ARTISTINFOWIDGET_H
#define ARTISTINFOWIDGET_H

#include <QPalette>
#include <QMap>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QUrl>
#include <QFont>
#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QScrollArea>
#include <QBuffer>
#include <QImage>
#include "abstractcontainer.h"
#include "../../../services/lastfmcontext.h"

class ArtistInfoWidget : public AbstractContainer
{
Q_OBJECT

public:
    explicit ArtistInfoWidget(QWidget *parent = 0);
    void songInformationUpdated(QMap<QString, QString> newContextInformation);
    void resetLabels();

private:
    LastFmContext *context;
    QMap<QString, QString> lastRequest;
    QImage pictureData;
    QNetworkReply *contextReply;


signals:

public slots:
    void updateContextInformation(QMap<QString, QString> newContextInformation);
    void showContextError();
};


#endif // ARTISTINFOWIDGET_H
