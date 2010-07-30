#include "applicationsettings.h"

void ApplicationSettings::initialisation() {
    qDebug("initialisation()");
    
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());
    settings.beginGroup("General");
    settings.setValue("version", QApplication::applicationVersion());
    settings.endGroup();
}


void ApplicationSettings::setTabOrder(QString tab, int value) {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    settings.beginGroup("TabOrder");
    settings.setValue(tab, value);
    settings.endGroup();
}


int ApplicationSettings::getTabOrder(QString tab) {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    settings.beginGroup("TabOrder");
    int position = settings.value(tab, -1).toInt();
    settings.endGroup();

    return position;
}

void ApplicationSettings::setSplitterSize(float value) {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    settings.beginGroup("Widgets");
    settings.setValue("SplitterRelativeSize", QString::number(value)); // Save as string only to make it readable
    settings.endGroup();
}

float ApplicationSettings::getSplitterSize() {
    QSettings settings(QSettings::UserScope, QApplication::organizationName(), QApplication::applicationName());

    settings.beginGroup("Widgets");
    float size = settings.value("SplitterRelativeSize", 0.25).toFloat();
    settings.endGroup();

    return size;
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

    // Get list of old values
    QStringList oldFolders = collectionFolderList();

    // Clear old values from settings file
    settings.remove("folders");

    settings.beginWriteArray("folders");
    for (int i = 0; i < folders.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("path", folders.at(i));

        // If we're adding a folder that does not exist, scan it!
        if (!oldFolders.contains(folders.at(i), Qt::CaseSensitive)) {
            qDebug("Parsing directory...");
            CollectionDatabase *cdb = CollectionDatabase::instance();
            cdb->scanDirectory(folders.at(i));
            delete cdb;
        }
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
