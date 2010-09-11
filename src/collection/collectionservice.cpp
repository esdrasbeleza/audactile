#include "collectionservice.h"

CollectionService::CollectionService(QObject *parent) :
    QThread(parent)
{
    watcher = new QFileSystemWatcher(this);
    collectionDb = new CollectionDatabase(this);

    QStringList directories = ApplicationSettings::collectionFolderList();
    if (!directories.isEmpty()) {
        // TODO: verify if every path is valid.
        watcher->addPaths(ApplicationSettings::collectionFolderList());
    }

    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));
    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(dirChanged(QString)));

}

void CollectionService::run() {
    scan();
}

QSqlTableModel *CollectionService::model() {
    return collectionDb->collectionModel();
}


void CollectionService::fileChanged(QString path) {
    qDebug("FILE CHANGED " + path.toUtf8());
}

void CollectionService::dirChanged(QString path) {
    qDebug("DIR CHANGED " + path.toUtf8());
}

void CollectionService::refresh() {
    setPaths(ApplicationSettings::collectionFolderList());

}

void CollectionService::scan() {
    QStringList directories = ApplicationSettings::collectionFolderList();
    foreach (QString path, directories) {
        scanRecursive(path);
    }
    emit listUpdated();
    qDebug("End of scan()");
}

void CollectionService::scanRecursive(QString path) {
    qDebug("scanRecursive " + path.toUtf8());

    // You shouldn't call this to add files
    if (QFileInfo(path).isFile()) return;

    QDir directory(path);
    foreach (QString fileEntry, directory.entryList(directory.AllEntries | directory.NoDotAndDotDot, directory.DirsFirst | directory.Name)) {
        // Change file entry to a full path
        fileEntry = directory.absolutePath() + directory.separator() + fileEntry;

        if (QFileInfo(fileEntry).isDir()) {
            scanRecursive(fileEntry);
        }
        else if (QFileInfo(fileEntry).isFile()) {
            Music *music = new Music(QUrl(fileEntry));
            if (collectionDb->addOrUpdateMusic(music)) {
                emit songAdded(music);
            }
        }
    }
}

void CollectionService::setPaths(QStringList paths) {
    watcher->removePaths(watcher->directories());

    // TODO: verify if every path is valid
    watcher->addPaths(paths);
}
