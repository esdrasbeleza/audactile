#include "applicationsettings.h"

void ApplicationSettings::initialisation() {
    qDebug("initialisation()");
    
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("General");
    settings.setValue("version", QApplication::applicationVersion());
    settings.endGroup();
}

void ApplicationSettings::createAppDirIfNeeded() {
    QString storageLocation = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir dir(storageLocation);
    if (!dir.exists()) {
        if (!dir.mkpath(storageLocation)) {
            qWarning("Could not create data directory.\n\nExiting...");
            QApplication::exit(1);
        }
    }
    else if (!dir.isReadable()) {
        qWarning("Could not read data directory.\n\nExiting...");
        QApplication::exit(1);
    }

}

QStringList ApplicationSettings::collectionFolderList() {
    qDebug("collectionFolderList()");

    
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    QStringList folders;
    int size = settings.beginReadArray("folders");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        folders.append(settings.value("path").toString());
    }
    folders.removeDuplicates();

    settings.endArray();
    // TODO: remove paths that do not exists.

    return folders;
}

void ApplicationSettings::addCollectionFolder(QString location) {
    
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    QStringList folders = collectionFolderList();
    folders.append(location);
    folders.removeDuplicates();
    settings.beginWriteArray("folders");
    for (int i = 0; i < folders.size(); ++i) {
        settings.setArrayIndex(i);
        qDebug(folders.at(i).toUtf8());
        settings.setValue("path", folders.at(i));
    }
    settings.endArray();
}

void ApplicationSettings::setCollectionFolders(QStringList folders) {
    
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    settings.remove("folders");

    settings.beginWriteArray("folders");
    for (int i = 0; i < folders.size(); ++i) {
        settings.setArrayIndex(i);
        qDebug(folders.at(i).toUtf8());
        settings.setValue("path", folders.at(i));
    }
    settings.endArray();
}


void ApplicationSettings::removeColletionFolder(QString location) {
    
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    QStringList folders = collectionFolderList();
    folders.append(location);
    folders.removeAll(location);
    settings.beginWriteArray("folders");
    for (int i = 0; i < folders.size(); ++i) {
        settings.setArrayIndex(i);
        qDebug(folders.at(i).toUtf8());
        settings.setValue("path", folders.at(i));
    }
    settings.endArray();
}
