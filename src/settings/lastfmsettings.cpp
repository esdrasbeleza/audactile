#include "lastfmsettings.h"

void LastFmSettings::setUsername(QString username) {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("lastfm");
    settings.setValue("username", username);
    settings.endGroup();
}


void LastFmSettings::setPassword(QString password) {
    QByteArray text = password.toUtf8();
    password = QString(text.toBase64());
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("lastfm");
    settings.setValue("password", password);
    settings.endGroup();
}

void LastFmSettings::setActive(bool active) {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("lastfm");
    settings.setValue("active", active);
    settings.endGroup();
}

QString LastFmSettings::username() {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("lastfm");
    QString ret;
    if (settings.contains("username")) {
        ret = settings.value("username").toString();
    }
    settings.endGroup();
    return ret;
}


QString LastFmSettings::password() {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("lastfm");
    QString ret;
    if (settings.contains("password")) {
        QByteArray text = settings.value("password").toByteArray();
        text = QByteArray::fromBase64(text);
        ret = QString(text);
    }
    settings.endGroup();
    return ret;
}


bool LastFmSettings::isActive() {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("lastfm");
    bool ret = false;
    if (settings.contains("active")) {
        ret = settings.value("active").toBool();
    }
    settings.endGroup();
    return ret;
}
