#include "mainwindow.h"

/// @brief Construtor.
/// 
/// @param parent Parent widget
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setObjectName("MainWindow");
    setWindowTitle("Audactile");
    setMinimumWidth(800);

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

    // Create a vertical layout
    QWidget *mainVerticalWidget = new QWidget();
    QVBoxLayout *verticalLayout = new QVBoxLayout();

    verticalLayout->addWidget(middleSplitter);
    mainVerticalWidget->setLayout(verticalLayout);
    setCentralWidget(mainVerticalWidget);

    // Includes our toolbar with more widgets, friendly called PlayerBar
    PlayerBar *playerbar = new PlayerBar(this, mediaObject, audioOutput);
    connect(playlistWidget, SIGNAL(songInformationUpdated(QMap<QString,QString>)), playerbar, SLOT(updateSongInformation(QMap<QString,QString>)));
    connect(playerbar, SIGNAL(nextButtonClicked()), playlistWidget, SLOT(playNextSong()));
    connect(playerbar, SIGNAL(previousButtonClicked()), playlistWidget, SLOT(playPreviousSong()));
    addToolBar(playerbar);
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


