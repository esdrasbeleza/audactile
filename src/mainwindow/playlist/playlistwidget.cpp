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
    setDropIndicatorShown(true);

    // Alternate row colors are good
    setAlternatingRowColors(true);

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
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(playSong(QTreeWidgetItem*)));
    connect(mainMediaObject, SIGNAL(aboutToFinish()), this, SLOT(enqueueNextSong()));
    connect(mainMediaObject, SIGNAL(finished()), this, SLOT(removeBold()));
    connect(mainMediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(handleStateChange(Phonon::State)));
    connect(mainMediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)), this, SLOT(fileChanged()));
}

void PlaylistWidget::playSong(QTreeWidgetItem *doubleClickedItem) {
    qDebug("playSong ");
    PlaylistItem *item = static_cast<PlaylistItem *>(doubleClickedItem);
    if (currentSong != NULL) {
        qDebug("Removing bold...");
        currentSong->removeBold();
    }
    currentSong = item;
    item->setBold();
    qDebug("Playing " + item->getFileUrl().path().toUtf8());
    mainMediaObject->setCurrentSource(item->getFileUrl());
    mainMediaObject->play();

    emitSongInformationUpdated();
}


void PlaylistWidget::playPreviousSong() {
    qDebug("playPreviousSong");
    QModelIndex index = indexAbove(indexFromItem(currentSong));
    if (index.isValid()) {
       playSong(itemFromIndex(index));
    }
}

void PlaylistWidget::playNextSong() {
    qDebug("playNextSong");
    QModelIndex index = indexBelow(indexFromItem(currentSong));
    if (index.isValid()) {
       playSong(itemFromIndex(index));
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

void PlaylistWidget::addSong(PlaylistItem *newItem, int index) {
    qDebug("addSong file");

    if (mainMediaObject->currentSource().type() == Phonon::MediaSource::Empty) {
        qDebug("First item added");
        currentSong = newItem;
        mainMediaObject->enqueue(newItem->getFileUrl());
    }

    newItem->index = index;
    connect(newItem, SIGNAL(validFile(PlaylistItem*)), this, SLOT(insertValidItem(PlaylistItem*)));
    connect(newItem, SIGNAL(invalidFile(PlaylistItem*)), this, SLOT(deleteInvalidItem(PlaylistItem*)));
}

void PlaylistWidget::addSong(QUrl url, int index) {
    qDebug("addSong URL " + QString::number(Phonon::MediaSource(url).type()).toUtf8());

    PlaylistItem *newItem = new PlaylistItem(url);
    addSong(newItem, index);
}

void PlaylistWidget::insertValidItem(PlaylistItem *newItem) {
    int index = newItem->index;
    if (index == -1) {
        addTopLevelItem(newItem);
    }
    else {
        insertTopLevelItem(index, newItem);
    }
}

void PlaylistWidget::deleteInvalidItem(PlaylistItem *invalidItem) {
    delete invalidItem;
}

void PlaylistWidget::addFolder(QUrl url) {
    qDebug("addFolder " + url.path().toUtf8());

    // You shouldn't call this to add files, man.
    if (QFileInfo(url.path()).isFile()) return;

    QDir directory(url.path());
    foreach (QString fileEntry, directory.entryList(directory.AllEntries | directory.NoDotAndDotDot, directory.DirsFirst | directory.Name)) {
        // Change file entry to a full path
        fileEntry = directory.absolutePath() + directory.separator() + fileEntry;
        qDebug("Parsing " + fileEntry.toUtf8());
        if (QFileInfo(fileEntry).isDir()) {
            qDebug("Adding folder " + fileEntry.toUtf8());
            addFolder(QUrl(fileEntry));
        }
        else if (QFileInfo(fileEntry).isFile()) {
            qDebug("Adding file " + fileEntry.toUtf8());
            addSong(QUrl(fileEntry));
        }
    }
}



void PlaylistWidget::dragEnterEvent(QDragEnterEvent *event) {
    qDebug("dragEnterEvent ");


    if (event->mimeData()->hasFormat("text/uri-list")) {
        qDebug("Accepted!");
        event->accept();
    }
    else {
        qDebug("Ignored!");
        event->ignore();
    }
}


void PlaylistWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->accept();
    }
}


void PlaylistWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug("mouseMoveEvent");

    // if not left button - return
    if (!(event->buttons() & Qt::LeftButton)) return;

    // if no item selected, return (else it would crash)
    if (currentItem() == NULL) return;

    drag = new QDrag(this);
    connect(drag, SIGNAL(actionChanged(Qt::DropAction)), this, SLOT(dndActionChanged(Qt::DropAction)));
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
    qDebug("Starting drag");
    QList<QTreeWidgetItem *> itemsToRemove = selectedItems();
    drag->exec(Qt::CopyAction | Qt::MoveAction);
}


void PlaylistWidget::dropEvent(QDropEvent *event) {
    qDebug("dropEvent ");

    if (event->mimeData()->hasFormat("text/uri-list")) {

        /*
         * If the dropped objects come from outside, we parse them as
         * a list of files, if they are a list of files.
         */
        if (event->source() != this) {
            qDebug("Parsing uri-list");
            QList<QUrl> urlList = event->mimeData()->urls();
            foreach (QUrl url, urlList) {
                qDebug("Trying to add new file: " + url.path().toUtf8());

                // If it's not a dir, add it using addSong
                if (QFileInfo(url.path()).isFile()) {
                    int index = indexOfTopLevelItem(itemAt(event->pos()));
                    addSong(url, index);
                }
                // If it's a folder, add it recursively
                else if (QFileInfo(url.path()).isDir()) {
                    qDebug("Add folder");
                    addFolder(url);
                }

            }
        }

        /*
         * If the dropped objects come from the playlist widget,
         * so we are moving the items from list.
         */
        else {
            qDebug("Moving from inside");
            QList<QTreeWidgetItem *> itemsToInsert;

            // Create the list of items to add...
            foreach (QTreeWidgetItem *currentItem, selectedItems()) {
                QTreeWidgetItem *playlistCurrentItem = takeTopLevelItem(indexOfTopLevelItem(currentItem));
                itemsToInsert.append(playlistCurrentItem);
            }

            // ...and insert them
            if (itemsToInsert.size() > 0) {
                int indexToInsert = indexOfTopLevelItem(itemAt(event->pos()));
                /*
                 * If the index the cursor is over is -1, there's no item under
                 * the cursor, so we must add the selected items to the end of
                 * the list.
                 */
                if (indexToInsert != -1) { insertTopLevelItems(indexToInsert, itemsToInsert); }
                else { addTopLevelItems(itemsToInsert); }
            }
        }
    }

    else {
        QTreeWidget::dropEvent(event);
    }



}

Qt::DropActions PlaylistWidget::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}


void PlaylistWidget::dndActionChanged(Qt::DropAction newAction) {
    qDebug("dndActionChanged()");
    dndAction = newAction;
    if (newAction == Qt::MoveAction) {
        qDebug("Move action");
    }
    else if (newAction == Qt::CopyAction) {
        qDebug("Copy action");
    }
}
