#ifndef LASTFMSETTINGS_H
#define LASTFMSETTINGS_H

#include <QApplication>
#include <QString>
#include <QSettings>
#include <QByteArray>

class LastFmSettings
{
public:
    static QString username();
    static QString password();
    static bool isActive();
    static void setUsername(QString username);
    static void setPassword(QString password);
    static void setActive(bool active);



};

#endif // LASTFMSETTINGS_H
