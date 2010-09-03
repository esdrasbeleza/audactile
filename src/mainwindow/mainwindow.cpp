#include "mainwindow.h"

/// @brief Construtor.
/// 
/// @param parent Parent widget
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setObjectName("MainWindow");
    setWindowTitle("Audactile");
    setMinimumWidth(700);
    setMinimumHeight(500);

    // Set strong focus, to capture all keyboard events
    setFocusPolicy(Qt::StrongFocus);

    // Our Phonon MediaObject
    mediaObject = new Phonon::MediaObject(this);
    mediaObject->setTickInterval(1000);
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(mediaObject, audioOutput);
    connect(audioOutput, SIGNAL(mutedChanged(bool)), this, SLOT(handleMute(bool)));
    connect(audioOutput, SIGNAL(volumeChanged(qreal)), this, SLOT(handleVolume(qreal)));

    // Connect the MediaObject to our Last.fm scrobbler
    LastFmScrobbler *scrobbler = new LastFmScrobbler(mediaObject);

    // Creates the horizontal layout where we'll put our notebook
    middleSplitter = new QSplitter();
    connect(middleSplitter, SIGNAL(splitterMoved(int,int)), this, SLOT(saveSplitterSize(int, int)));
    playlistWidget = new PlaylistWidget(this, mediaObject);
    mainNotebook = new MainNotebook(this, playlistWidget); // Notebook needs to connect context to playlistwidget!
    // TODO: playlistWidget must be a singleton.
    mainNotebook->setMinimumWidth(200);

    // Add widgets
    middleSplitter->addWidget(mainNotebook);
    middleSplitter->addWidget(playlistWidget);
    middleSplitter->setStretchFactor(0, 1);
    middleSplitter->setStretchFactor(1, 3);

    // Set splitter sizes to saved sizes, if existent
    int notebookSize = ceil(width() * ApplicationSettings::getSplitterSize());
    QList<int> sizes;
    sizes.append(notebookSize);
    sizes.append(width() - notebookSize);
    middleSplitter->setSizes(sizes);
    middleSplitter->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);

    // Includes our toolbar with more widgets, friendly called PlayerBar
    PlayerBar *playerbar = new PlayerBar(this, mediaObject, audioOutput);
    connect(playlistWidget, SIGNAL(songInformationUpdated(QMap<QString,QString>)), playerbar, SLOT(updateSongInformation(QMap<QString,QString>)));
    connect(playerbar, SIGNAL(nextButtonClicked()), playlistWidget, SLOT(playNextSong()));
    connect(playerbar, SIGNAL(previousButtonClicked()), playlistWidget, SLOT(playPreviousSong()));
    connect(playerbar, SIGNAL(toggleFullScreen()), this, SLOT(toggleFullscreen()));

    // Makes playerbar change the window state button
    connect(this, SIGNAL(windowStateChanged(Qt::WindowStates)), playerbar, SLOT(handleWindowStateChange(Qt::WindowStates)));

    // Create a vertical layout
    QWidget *mainVerticalWidget = new QWidget();
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    verticalLayout->addWidget(playerbar);
    verticalLayout->addWidget(middleSplitter);
    mainVerticalWidget->setLayout(verticalLayout);
    setCentralWidget(mainVerticalWidget);
}


// Handle splitter movement
void MainWindow::saveSplitterSize(int pos, int index) {
    if (middleSplitter->widget(index) == playlistWidget) {
        ApplicationSettings::setSplitterSize((float)pos / width());
    }
}

/*
 *
 * The functions handleMute and handleVolume were created to avoid
 * the problems with Phonon::VolumeSlider, that was showing wrong
 * volume = 0% when volume was unmuted.
 *
 */


void MainWindow::handleMute(bool mute) {
    if (!mute) {
        audioOutput->setVolume(outputVolume);
    }
}
void MainWindow::handleVolume(qreal volume) {
    outputVolume = volume;
}


// Handle keyboard events
void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Space:
    case Qt::Key_Enter:
    case Qt::Key_MediaPlay: // Will not work in Linux, verify Mac and Windows
    case Qt::Key_Play:      // Will not work in Linux, verify Mac and Windows
    case Qt::Key_Return:
        qDebug("Play key pressed!");
        event->accept();
        break;

    // Full screen support!
    case Qt::Key_F11:
        toggleFullscreen();
        event->accept();
        break;
    default:
        event->ignore();
        break;
    }
}

// TODO: add button to toggle fullscreen mode.
void MainWindow::toggleFullscreen() {
    if (windowState() != Qt::WindowFullScreen) {
        originalWindowState = windowState();
        showFullScreen();
    }
    else {
        switch (originalWindowState) {
        case Qt::WindowNoState:
            showNormal();
            break;
        case Qt::WindowMinimized:
            showMinimized();
            break;
        default:
            showMaximized();
            break;
        }
    }
    emit windowStateChanged(windowState());
}
