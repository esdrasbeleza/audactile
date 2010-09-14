#include "collectionservice.h"

CollectionService::CollectionService(QObject *parent) :
    QThread(parent)
{
    watcher = new QFileSystemWatcher(this);
    collectionDb = new CollectionDatabase(this);

    // Set watcher paths to paths in settings file
    refresh();

    connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));
    connect(watcher, SIGNAL(directoryChanged(QString)), this, SLOT(dirChanged(QString)));

}

void CollectionService::run() {
    verifyFiles();
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

/*
 * Verify if all files in database exist.
 */
void CollectionService::verifyFiles() {
    QSqlTableModel *collectionModel = model();
    while (collectionModel->canFetchMore()) collectionModel->fetchMore();
    int total = collectionModel->rowCount();

    for (int i = 0; i < total; i++) {
        QString path = collectionModel->record(i).value(collectionModel->fieldIndex("path")).toString();
        if (!QFileInfo(path).exists()) {
            collectionDb->removeMusic(path);
            emit songRemoved(path);
        }
    }

    delete collectionModel;
}

/*
 * Scan collection folders in order to assert that
 * all files in folders are in collection.
 */
void CollectionService::scan() {
    QStringList directories = ApplicationSettings::collectionFolderList();
    foreach (QString path, directories) {
        scanRecursive(path);
    }
    emit listUpdated();
}

void CollectionService::scanRecursive(QString path) {
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
    if (!watcher->directories().isEmpty()) {
        watcher->removePaths(watcher->directories());
    }

    // TODO: verify if every path is valid
    QStringList directories = ApplicationSettings::collectionFolderList();
    if (!directories.isEmpty()) {
        watcher->addPaths(ApplicationSettings::collectionFolderList());
    }
}
