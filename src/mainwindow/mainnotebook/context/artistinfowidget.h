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
#include "../../../services/lastfmcontext.h"

class ArtistInfoWidget : public QScrollArea
{
Q_OBJECT

public:
    explicit ArtistInfoWidget(QWidget *parent = 0);
    void songInformationUpdated(QMap<QString, QString> newContextInformation);

private:
    LastFmContext *context;
    QMap<QString, QString> lastRequest;
    QLabel *artistLabel;
    QLabel *summaryLabel;
    QLabel *pictureLabel;
    QLabel *moreLinkLabel;

    QImage pictureData;
    void resetLabels();
    QNetworkReply *contextReply;
    QBuffer *pictureBuffer;


signals:

public slots:
    void updateContextInformation(QMap<QString, QString> newContextInformation);
    void readPictureReply();
    void showPicture();
};


#endif // ARTISTINFOWIDGET_H
