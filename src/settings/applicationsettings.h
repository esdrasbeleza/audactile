#ifndef APPLICATIONSETTINGS_H
#define APPLICATIONSETTINGS_H

#include <QSettings>
#include <QtGui/QApplication>
#include <QStringList>

class ApplicationSettings
{
public:
    ApplicationSettings();
    void initialisation();
    QStringList collectionFolderList();
    void addCollectionFolder(QString location);
    void removeColletionFolder(QString location);
    void setCollectionFolders(QStringList folders);

private:
    QSettings settings;

};

#endif // APPLICATIONSETTINGS_H
