#include "collectionitem.h"

CollectionItem::CollectionItem(QString filePath, QObject *parent) :
    QObject(parent)
{
    qDebug("new CollectionItem: " + filePath.toUtf8());
    metaDataResolver = new Phonon::MediaObject(this);
    connect(metaDataResolver, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(loadMetaData(Phonon::State)));
    QUrl fileUrl = QUrl().fromLocalFile(filePath);
    metaDataResolver->setCurrentSource(fileUrl);

    this->filePath = filePath;
    this->fileName = QFileInfo(filePath).fileName();
}


void CollectionItem::loadMetaData(Phonon::State newState) {
    qDebug("loadMetaData");

    if (newState == Phonon::ErrorState) {
        qDebug("Error!");
        return;
    }

    if (metaDataResolver->currentSource().type() == Phonon::MediaSource::Invalid) {
        qDebug("Error!");
        return;
    }

    // If duration is greater than -1, it's a valid file
    qint64 duration = metaDataResolver->totalTime();
    if (duration > -1) {
        QMap<QString, QString> metaData = metaDataResolver->metaData();
        artist = metaData.value("ARTIST");
        album = metaData.value("ALBUM");
        title = metaData.value("TITLE");

        if (artist.isEmpty()) artist = "Undefined";
        if (album.isEmpty())  album  = "Undefined";
        if (title.isEmpty())  title  = filePath;

        emit validFile(this);
        qDebug("Sinal emitido!");
    }
    else {
        emit invalidFile(this);
    }
}

QString CollectionItem::getArtist() {
    return artist;
}
