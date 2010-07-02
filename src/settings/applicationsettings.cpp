#include "applicationsettings.h"

ApplicationSettings::ApplicationSettings()
{
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    qDebug(settings.fileName().toUtf8());

}

void ApplicationSettings::initialisation() {
    qDebug("initialisation()");
    settings.beginGroup("General");
    settings.setValue("version", QApplication::applicationVersion());
    settings.endGroup();

}

QStringList ApplicationSettings::collectionFolderList() {
    qDebug("collectionFolderList()");
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
