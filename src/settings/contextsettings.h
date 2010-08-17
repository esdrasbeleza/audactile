#ifndef CONTEXTSETTINGS_H
#define CONTEXTSETTINGS_H

#include <QApplication>
#include <QString>
#include <QSettings>

class ContextSettings
{
public:
    static void setFetchArtistInfoActive(bool active);
    static void setFetchLyricsActive(bool active);
    static bool isFetchArtistInfoActive();
    static bool isFetchLyricsActive();

};

#endif // CONTEXTSETTINGS_H
