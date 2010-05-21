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


    // Creates the horizontal layout where we'll put our notebook
    QSplitter *middleSplitter = new QSplitter();
    MainNotebook *mainNotebook = new MainNotebook(this);
    mainNotebook->setMinimumWidth(200);
    playlistWidget = new PlaylistWidget(this, mediaObject);
    middleSplitter->addWidget(mainNotebook);
    middleSplitter->addWidget(playlistWidget);
    middleSplitter->setStretchFactor(0, 1);
    middleSplitter->setStretchFactor(1, 4);

    // Create a vertical layout
    QWidget *mainVerticalWidget = new QWidget();
    QVBoxLayout *verticalLayout = new QVBoxLayout();


    verticalLayout->addWidget(middleSplitter);
    mainVerticalWidget->setLayout(verticalLayout);
    setCentralWidget(mainVerticalWidget);

    // Includes our toolbar with more widgets, friendly called PlayerBar
    PlayerBar *playerbar = new PlayerBar(this, mediaObject, audioOutput);
    connect(playlistWidget, SIGNAL(songInformationUpdated(QString)), playerbar, SLOT(updateSongInformation(QString)));
    connect(playerbar, SIGNAL(nextButtonClicked()), playlistWidget, SLOT(playNextSong()));
    connect(playerbar, SIGNAL(previousButtonClicked()), playlistWidget, SLOT(playPreviousSong()));
    addToolBar(playerbar);
}

