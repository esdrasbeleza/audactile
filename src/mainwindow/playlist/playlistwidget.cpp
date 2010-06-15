#include "playlistwidget.h"



/*
 * TODO:
 * - Fix columns size
 * - more columns, like rating
 */

PlaylistWidget::PlaylistWidget(QWidget *parent, Phonon::MediaObject *mediaObject) : QTreeWidget(parent)
{
    setObjectName("PlaylistWidget");
    setColumnCount(4);

    currentSong = NULL;
    nextSong = NULL;

    setSelectionMode(QAbstractItemView::ExtendedSelection);

    // Allow drop to use drag and drop
    setAcceptDrops(true);
    setDragEnabled(true);

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
    qDebug("playSong ");
    PlaylistItem *item = static_cast<PlaylistItem *>(index.internalPointer());
    if (currentSong != NULL) {
        currentSong->removeBold();
    }
    currentSong = item;
    item->setBold();
    mainMediaObject->setCurrentSource(item->getFileUrl());
    qDebug("Playing " + item->getFileUrl().toString().toUtf8());
    mainMediaObject->play();

    emitSongInformationUpdated();
}


void PlaylistWidget::playPreviousSong() {
    qDebug("playPreviousSong");
    QModelIndex index = indexAbove(indexFromItem(currentSong));
    if (index.isValid()) {
       playSong(index);
    }
}

void PlaylistWidget::playNextSong() {
    qDebug("playNextSong");
    QModelIndex index = indexBelow(indexFromItem(currentSong));
    if (index.isValid()) {
       playSong(index);
    }
}


void PlaylistWidget::enqueueNextSong() {
    qDebug("enqueueNextSong");
    nextSong = (PlaylistItem*)itemBelow(currentSong);
    if (nextSong != NULL) {
        mainMediaObject->enqueue(nextSong->getFileUrl());
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
        qDebug("First item added");
        currentSong = newItem;
        mainMediaObject->enqueue(newItem->getFileUrl());
    }
    addTopLevelItem(newItem);
}

void PlaylistWidget::addSong(QUrl url) {
    qDebug("addSong");
    PlaylistItem *newItem = new PlaylistItem(url);
    addSong(newItem);
}


void PlaylistWidget::dragEnterEvent(QDragEnterEvent *event) {
    qDebug("dragEnterEvent ");


    if (event->mimeData()->hasFormat("text/uri-list")) {
        qDebug("Accepted!");
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else {
        qDebug("Ignored!");
        event->ignore();
    }
}


void PlaylistWidget::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug("dragMoveEvent");
    event->setDropAction(Qt::MoveAction);
    event->accept();
}


void PlaylistWidget::mouseMoveEvent(QMouseEvent *event)
{
    // if not left button - return
    if (!(event->buttons() & Qt::LeftButton)) return;

    // if no item selected, return (else it would crash)
    if (currentItem() == NULL) return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    // construct list of QUrls
    // other widgets accept this mime type, we can drop to them
    QList<QUrl> list;

    foreach (QTreeWidgetItem *currentItem, selectedItems()) {
        PlaylistItem *playlistCurrentItem = static_cast<PlaylistItem *>(currentItem);
        list.append(playlistCurrentItem->getFileUrl());
    }

    // mime stuff
    mimeData->setUrls(list);
    drag->setMimeData(mimeData);

    // start drag
    drag->exec(Qt::CopyAction | Qt::MoveAction);
}


void PlaylistWidget::dropEvent(QDropEvent *event) {
    qDebug("dropEvent ");

    if (event->mimeData()->hasFormat("text/uri-list")) {
        qDebug("Parsing uri-list");
        QList<QUrl> urlList = event->mimeData()->urls();
        foreach (QUrl url, urlList) {
            qDebug("Trying to add new file: " + url.path().toUtf8());
            addSong(url);
        }
    }

}
