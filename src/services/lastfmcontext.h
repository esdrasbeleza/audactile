#ifndef LASTFMCONTEXT_H
#define LASTFMCONTEXT_H

#include <QTextDocument>
#include <QObject>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QXmlQuery>
#include <QStringList>
#include <QMap>


class LastFmContext : public QObject
{
Q_OBJECT
public:
    explicit LastFmContext(QObject *parent = 0);
    void getInfo(QString artist);

private:
    QNetworkAccessManager *netManager;
    QNetworkReply *contextReply;
    QMap<QString, QString> contextData;

signals:
    void contextUpdated(QMap<QString, QString> contextData);    

private slots:
    void readContextReply();

};

#endif // LASTFMCONTEXT_H
