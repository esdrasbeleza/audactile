#include "collectiondatabase.h"
CollectionDatabase* CollectionDatabase::m_Instance = 0;

CollectionDatabase* CollectionDatabase::instance()  {
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();
        if (!m_Instance) { m_Instance = new CollectionDatabase(new QObject); }
        mutex.unlock();
    }
    return m_Instance;
}


CollectionDatabase::CollectionDatabase(QObject *parent) : QObject(parent) {
}

CollectionDatabase::CollectionDatabase(const CollectionDatabase&, QObject *parent) : QObject(parent)
{
    qDebug("CollectionDatabase Constructor!");
}


void CollectionDatabase::scanDirectory(QDir directory) {
    QStringList files = directory.entryList(QDir::Readable);

    foreach (QString fileEntry, directory.entryList(directory.AllEntries | directory.NoDotAndDotDot, directory.DirsFirst | directory.Name)) {
        // Change file entry to a full path
        fileEntry = directory.absolutePath() + directory.separator() + fileEntry;
        if (QFileInfo(fileEntry).isDir()) {
            qDebug("Adding folder " + fileEntry.toUtf8());
            scanDirectory(fileEntry);
        }
        else if (QFileInfo(fileEntry).isFile()) {
            qDebug("Adding file " + fileEntry.toUtf8());
            CollectionItem *item = new CollectionItem(fileEntry, this);
            connect(item, SIGNAL(validFile(CollectionItem*)), this, SLOT(addSong(CollectionItem*)));
        }
    }

}

void CollectionDatabase::addSong(CollectionItem *validFile) {
    qDebug(validFile->getArtist().toUtf8());
}
