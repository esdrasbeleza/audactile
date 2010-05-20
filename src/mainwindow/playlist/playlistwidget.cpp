#include "playlistwidget.h"



/*
 * TODO:
 * - Fix columns size
 * - more columns, like rating
 */

PlaylistWidget::PlaylistWidget(QWidget *parent, Phonon::MediaObject *mediaObject)
{
    setParent(parent);
    setObjectName("PlaylistWidget");
    setColumnCount(4);

    currentSong = NULL;
    nextSong = NULL;

    // Phonon MediaObject
    mainMediaObject = mediaObject;


    // Define titles for labels
    QStringList playlistWidgetHeaders;
    playlistWidgetHeaders.append("Title");
    playlistWidgetHeaders.append("Album");
    playlistWidgetHeaders.append("Artist");
    playlistWidgetHeaders.append("Duration");
    setHeaderLabels(playlistWidgetHeaders);

    // Set alignment for the columns' headers
    QHeaderView *headers = header();
    headers->setDefaultAlignment(Qt::AlignCenter);
    headers->setSortIndicatorShown(true);

    // Assign signals
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playSong(QModelIndex)));
    connect(mainMediaObject, SIGNAL(aboutToFinish()), this, SLOT(enqueueNextSong()));
    connect(mainMediaObject, SIGNAL(finished()), this, SLOT(removeBold()));
    connect(mainMediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(handleStateChange(Phonon::State)));
    connect(mainMediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)), this, SLOT(fileChanged()));
}


void PlaylistWidget::playSong(QModelIndex index) {
    qDebug("playSong");
    PlaylistItem *item = static_cast<PlaylistItem *>(index.internalPointer());
    if (currentSong != NULL) {
        currentSong->removeBold();
    }
    currentSong = item;
    item->setBold();
    mainMediaObject->setCurrentSource(item->getFilePath());
    mainMediaObject->play();

    emitSongInformationUpdated();
}


void PlaylistWidget::enqueueNextSong() {
    qDebug("enqueueNextSong");
    nextSong = (PlaylistItem*)itemBelow(currentSong);
    if (nextSong != NULL) {
        mainMediaObject->enqueue(nextSong->getFilePath());
    }
}

void PlaylistWidget::removeBold() {
    currentSong->removeBold();
}

void PlaylistWidget::fileChanged() {
    qDebug("fileChanged");
    if (nextSong != NULL) {
        currentSong->removeBold();
        currentSong = nextSong;
        nextSong = NULL;
    }

}

void PlaylistWidget::handleStateChange(Phonon::State newState) {
    if (newState > Phonon::StoppedState) {
        qDebug("Asking to update song information after changing to state " + QString::number(newState).toUtf8());
        currentSong->setBold();
        emitSongInformationUpdated();
    }
    else {
        if (currentSong != NULL) {
            currentSong->removeBold();
        }
    }
}

void PlaylistWidget::emitSongInformationUpdated() {
    qDebug("emitSongInformationUpdated");
    QString songInfo = QString(currentSong->getSongInfo());
    emit songInformationUpdated(songInfo);
}

void PlaylistWidget::addSong(PlaylistItem *newItem) {
    qDebug("addSong");
    if (mainMediaObject->currentSource().type() == Phonon::MediaSource::Empty) {
        qDebug("First item added: " + newItem->getFilePath().toUtf8());
        currentSong = newItem;
        mainMediaObject->enqueue(newItem->getFilePath());
    }
    addTopLevelItem(newItem);
}

