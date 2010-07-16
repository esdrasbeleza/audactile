#ifndef LASTFMCONTEXT_H
#define LASTFMCONTEXT_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class LastFmContext : public QObject
{
Q_OBJECT
public:
    LastFmContext(QString artist, QObject *parent = 0);

private:
    // Network related stuff
    enum GetContextState  {
        GetContextNone = 0,
        GetContextWaitingResponse = 1
    };
    GetContextState state;

signals:

public slots:



};

#endif // LASTFMCONTEXT_H
