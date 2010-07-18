#ifndef CONTEXTWIDGET_H
#define CONTEXTWIDGET_H

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QUrl>
#include "../../../services/lastfmcontext.h"

class ContextWidget : public QWidget
{
Q_OBJECT
public:
    explicit ContextWidget(QWidget *parent = 0);

private:
    LastFmContext *context;
    QMap<QString, QString> lastRequest;
    QLabel *artistLabel;
    QLabel *summaryLabel;
    QLabel *pictureLabel;
    void resetLabels();


signals:

public slots:
    void songInformationUpdated(QMap<QString, QString> newContextInformation);
    void updateContextInformation(QMap<QString, QString> newContextInformation);
};

#endif // CONTEXTWIDGET_H
