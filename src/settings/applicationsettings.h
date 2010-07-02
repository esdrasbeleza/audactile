#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QApplication>
#include <QSettings>
#include <QtGui/QApplication>
#include <QStringList>
#include <QDesktopServices>
#include <QDir>

class ApplicationSettings
{
public:
    ApplicationSettings();
    void initialisation();
    QStringList collectionFolderList();
    void addCollectionFolder(QString location);
    void removeColletionFolder(QString location);
    void setCollectionFolders(QStringList folders);
    void createAppDirIfNeeded();

private:
    QSettings settings;

};

#endif // APPLICATIONSETTINGS_H
