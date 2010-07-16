#include "lastfmcontext.h"

LastFmContext::LastFmContext(QString artist, QObject *parent) :
    QObject(parent)
{
    QUrl url("http://ws.audioscrobbler.com/2.0/");
    url.addQueryItem("artist", artist);
    url.addQueryItem("api_key", "ee988217b1695e36e1447dc0de443ac3");

    state = GetContextWaitingResponse;
    QNetworkRequest netRequest;
    netRequest.setUrl(url);

}
