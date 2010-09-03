#include "collectionhandler.h"

/*
 *
 * URGENT TODO:
 *
 * PUT THIS INTO A SEPARATE THREAD.
 *
 */
CollectionHandler::CollectionHandler(QObject *parent) :
    QObject(parent)
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

void CollectionHandler::fileChanged(QString path) {
    qDebug("FILE CHANGED " + path.toUtf8());
}

void CollectionHandler::dirChanged(QString path) {
    qDebug("DIR CHANGED " + path.toUtf8());
}

void CollectionHandler::refresh() {
    setPaths(ApplicationSettings::collectionFolderList());

}

void CollectionHandler::scan() {
    QStringList directories = ApplicationSettings::collectionFolderList();
    foreach (QString path, directories) {
        scanRecursive(path);
    }
    qDebug("End of scan()");
}

void CollectionHandler::scanRecursive(QString path) {
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
            // TODO: should I add this directly or emit a signal?
            collectionDb->addMusic(fileEntry);
        }
    }
}

void CollectionHandler::setPaths(QStringList paths) {
    watcher->removePaths(watcher->directories());

    // TODO: verify if every path is valid
    watcher->addPaths(paths);
}
