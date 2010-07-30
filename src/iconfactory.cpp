#include "iconfactory.h"

#ifdef Q_WS_X11
QIcon IconFactory::fromTheme(QString iconName) {
    return QIcon::fromTheme(iconName);
}

#else
/*
 * TODO: icons that will be used in Mac OS and Windows
 */
QIcon IconFactory::fromTheme(QString iconName) {
    //QIcon::setThemeSearchPaths(QStringList() << QLatin1String(":/icons"));
    QIcon::setThemeName("oxygen");
    return QIcon::fromTheme(iconName);
}

#endif
