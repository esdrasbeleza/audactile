#include "iconfactory.h"

#ifdef Q_WS_X11
QIcon IconFactory::fromTheme(QString iconName) {
    // qDebug("=== " + iconName.toUtf8());
    return QIcon::fromTheme(iconName);
}

#else
/*
 * TODO: icons that will be used in Mac OS and Windows
 */
QIcon IconFactory::fromTheme(QString iconName) {
    QIcon::setThemeSearchPaths(QStringList() << QLatin1String(":/icons"));
    QIcon::setThemeName("gnome");
    return QIcon::fromTheme(iconName);
}

#endif
