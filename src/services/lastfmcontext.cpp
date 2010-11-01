#include "lastfmcontext.h"

LastFmContext::LastFmContext(QObject *parent) :
    QObject(parent)
{
    netManager = new QNetworkAccessManager(this);
}

void LastFmContext::getInfo(QString artist) {
    QUrl url("http://ws.audioscrobbler.com/2.0/");
    url.addQueryItem("method", "artist.getinfo");
    url.addQueryItem("artist", artist.toUtf8());
    url.addQueryItem("api_key", "ee988217b1695e36e1447dc0de443ac3");

    QNetworkRequest netRequest;
    netRequest.setUrl(url);
    contextReply = netManager->get(netRequest);
    connect(contextReply, SIGNAL(finished()), this, SLOT(readContextReply()));
    connect(contextReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(contextError())); // TODO: specify which error was given
}

void LastFmContext::readContextReply() {
    QString replyString = QString::fromUtf8(contextReply->readAll());

    if (replyString.isEmpty()) {
        return; // Avoid empty parsing of XML
    }

    // Parametres
    QString status;
    QString artistName;
    QString artistPicture;
    QString artistSummary;
    QString artistProfile;

    QXmlQuery query;
    query.setFocus(replyString);
    query.setQuery("lfm[@status = 'ok']/count(artist)");
    query.evaluateTo(&status);
    status = status.trimmed();

    /*
     * If we got the data successfully, let's read it.
     * I hate XML.
     */
    if (status == "1") {
        query.setQuery("lfm/artist/name/text()");
        query.evaluateTo(&artistName);
        artistName = artistName.trimmed();

        query.setQuery("lfm/artist/url/text()");
        query.evaluateTo(&artistProfile);
        artistProfile = artistProfile.trimmed();

        query.setQuery("lfm/artist/image[@size=\"extralarge\"]/text()");
        query.evaluateTo(&artistPicture);
        artistPicture = artistPicture.trimmed();

        // Summary has HTML entities that must be un-replaced.
        query.setQuery("lfm/artist/bio/summary/text()");
        query.evaluateTo(&artistSummary);
        artistSummary = artistSummary.trimmed().replace("&lt;","<").replace("&gt;",">");

        // Store the context data into... contextData. Nice!
        contextData.clear();
        contextData.insert("artist", artistName);
        contextData.insert("picture", artistPicture);
        contextData.insert("summary", artistSummary);
        contextData.insert("profile", artistProfile);

        // Emit the signal
        emit contextUpdated(contextData);
    }
    else {
        qDebug("LastFmContext: FAIL!");
        emit contextError();
    }
}
