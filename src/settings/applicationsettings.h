#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QApplication>
#include <QSettings>
#include <QtGui/QApplication>
#include <QStringList>
#include <QDesktopServices>
#include <QDir>
#include "../collection/collectiondatabase.h"

class ApplicationSettings
{
public:
    static void initialisation();
    static QStringList collectionFolderList();
    static void addCollectionFolder(QString location);
    static void removeColletionFolder(QString location);
    static void setCollectionFolders(QStringList folders);
    static void createAppDirIfNeeded();

private:
    QSettings qsettings;

};

#endif // APPLICATIONSETTINGS_H
