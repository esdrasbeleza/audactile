#include "contextsettings.h"

void ContextSettings::setFetchArtistInfoActive(bool active) {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("context");
    settings.setValue("fetch_artist_info", active);
    settings.endGroup();
}

bool ContextSettings::isFetchArtistInfoActive() {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("context");
    bool ret = settings.value("fetch_artist_info", true).toBool();
    settings.endGroup();
    return ret;
}

void ContextSettings::setFetchLyricsActive(bool active) {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("context");
    settings.setValue("fetch_lyrics", active);
    settings.endGroup();
}

bool ContextSettings::isFetchLyricsActive() {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("context");
    bool ret = settings.value("fetch_lyrics", false).toBool();
    settings.endGroup();
    return ret;
}
