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
    static void setTabOrder(QString tab, int value);
    static int  getTabOrder(QString tab);
    static void setSplitterSize(float value);
    static float  getSplitterSize();
    static void addCollectionFolder(QString location);
    static void removeColletionFolder(QString location);
    static void setCollectionFolders(QStringList folders);
    static void createAppDirIfNeeded();

private:
    QSettings qsettings;

};

#endif // APPLICATIONSETTINGS_H
