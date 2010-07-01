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

private:
    QSettings settings;

};

#endif // APPLICATIONSETTINGS_H
