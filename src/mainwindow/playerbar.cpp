#include "playerbar.h"

using namespace Phonon;

/// @brief Audactile's main toolbar class.
/// 
/// @param parent Parent widget
/// @param mediaObject MediaObject that will handle the files
/// @param audioOutput AudioOutput that will be linked to MediaObject
PlayerBar::PlayerBar(QWidget *parent, Phonon::MediaObject *mediaObject, Phonon::AudioOutput *audioOutput)
{
    setAllowedAreas(Qt::TopToolBarArea|Qt::BottomToolBarArea);
    setIconSize(QSize(36, 36));

    mainMediaObject = mediaObject;
    setParent(parent);

    // Buttons
    playButton = new QToolButton();
    stopButton = new QToolButton();
    exitButton = new QToolButton();
    nextButton = new QToolButton();
    previousButton = new QToolButton();
    prefButton = new QToolButton();

    playButton->setIcon(QIcon::fromTheme("media-playback-start"));
    stopButton->setIcon(QIcon::fromTheme("media-playback-stop"));
    nextButton->setIcon(QIcon::fromTheme("media-skip-forward"));
    previousButton->setIcon(QIcon::fromTheme("media-skip-backward"));
    prefButton->setIcon(QIcon::fromTheme("preferences-other"));
    exitButton->setIcon(QIcon::fromTheme("application-exit"));

    stopButton->setDisabled(true);

    // Signals from buttons
    connect(playButton, SIGNAL(clicked()), this, SLOT(handlePlayButton()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(handleStopButton()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(handleNextButton()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(handlePreviousButton()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitApplication()));

    // Vertical box with slider and current song time labels
    QFrame *songPositionWidget = new QFrame(this);
    songPositionWidget->setFrameShadow(QFrame::Sunken);
    songPositionWidget->setFrameShape(QFrame::StyledPanel);
    songPositionWidget->setMidLineWidth(4);


    // Horizontal box with current song position labels
    QWidget *songPositionLabelsWidget = new QWidget(this);
    QHBoxLayout *songPositionLabelsHBox = new QHBoxLayout(songPositionLabelsWidget);
    currentSongPosition = new QLabel(tr("--:--"));
    remainingSongPosition = new QLabel(tr("--:--"));
    currentSongInfo = new QLabel(tr(""));

    // Define song info to be bold
    QFont songInfoFont = currentSongInfo->font();
    songInfoFont.setBold(true);
    songInfoFont.setPointSize(songInfoFont.pointSize() + 2);
    currentSongInfo->setFont(songInfoFont);

    // Add labels
    songPositionLabelsHBox->addWidget(currentSongPosition, 1, Qt::AlignLeft);
    songPositionLabelsHBox->addWidget(currentSongInfo, 1, Qt::AlignCenter);
    songPositionLabelsHBox->addWidget(remainingSongPosition, 1, Qt::AlignRight);
    songPositionLabelsWidget->setLayout(songPositionLabelsHBox);

    
    // Set background for song position widget
    QPalette palette = songPositionWidget->palette();
    QLinearGradient songPositionBgGradient(1.0, 1.0, 1.0, 40.0);
    songPositionBgGradient.setColorAt(0, QColor(250,250,230));
    songPositionBgGradient.setColorAt(1, QColor(220,220,200));
    palette.setBrush(songPositionLabelsWidget->backgroundRole(), QBrush(songPositionBgGradient));
    palette.setColor(songPositionLabelsWidget->foregroundRole(), QColor(100,100,100));
    songPositionWidget->setPalette(palette);
    songPositionWidget->setAutoFillBackground(true);

    QVBoxLayout *songPositionVBox = new QVBoxLayout(songPositionWidget);
    songPositionSlider = new SeekSlider(mainMediaObject, this);
    songPositionSlider->setOrientation(Qt::Horizontal);
    songPositionVBox->addWidget(songPositionLabelsWidget);
    songPositionVBox->addWidget(songPositionSlider);
    songPositionWidget->setLayout(songPositionVBox);

    // Volume button
    Phonon::VolumeSlider *volumeSlider = new Phonon::VolumeSlider(audioOutput, this);
    volumeSlider->setMaximumWidth((int)floor(0.2*(window()->width())));

    addWidget(playButton);
    addWidget(stopButton);
    addSeparator();
    addWidget(previousButton);
    addWidget(nextButton);
    addSeparator();
    addWidget(songPositionWidget);
    addSeparator();
    addWidget(volumeSlider);
    addSeparator();
    addWidget(prefButton);
    addWidget(exitButton);

    // Signals from media source
    connect(mainMediaObject, SIGNAL(tick(qint64)), this, SLOT(updateSongPosition()));
    connect(mainMediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(handleState(Phonon::State,Phonon::State)));
    connect(mainMediaObject, SIGNAL(finished()), this, SLOT(finish()));

    show();
}



/// @brief Update current song position and remaining song time on playerbar.
void PlayerBar::updateSongPosition() {
    int secs, mins;
    QString qStr;

    /*
     * Get the remaining time. If we have more than 1000 ms, we
     * can update the time. The last second must not update the
     * playerbar, since after that the timer will become "--:--".
     */
    qint64 rem = mainMediaObject->remainingTime();
    if (rem > 1000) {
        qint64 cur = mainMediaObject->currentTime();

        songPositionSlider->setEnabled(true);

        secs = (rem / 1000) % 60;
        mins = (rem / 1000) / 60;
        remainingSongPosition->setText("-" + QString::number(mins) + ":" + qStr.sprintf("%02d", secs));

        secs = (cur / 1000) % 60;
        mins = (cur / 1000) / 60;
        currentSongPosition->setText(QString::number(mins) + ":" + qStr.sprintf("%02d", secs));
    }

}


/// @brief Handle the state change in the MediaObject.
/// 
/// @param newState New state
/// @param oldState Old state
void PlayerBar::handleState(Phonon::State newState, Phonon::State oldState) {
    // Handle play button
    if (newState == Phonon::PlayingState) {
        playButton->setIcon(QIcon::fromTheme("media-playback-pause"));
    }
    else if (newState == Phonon::StoppedState) {
        playButton->setIcon(QIcon::fromTheme("media-playback-start"));
    }
    else if (newState == Phonon::PausedState) {
        playButton->setIcon(QIcon::fromTheme("media-playback-start"));
    }

    // Handle stop button
    if (newState <= Phonon::StoppedState) {
        qDebug("Stopped state");
        stopButton->setDisabled(true);
    }
    else {
        stopButton->setEnabled(true);
    }
}


/// @brief Callback for play button
void PlayerBar::handlePlayButton() {
    if (mainMediaObject->state() == Phonon::PlayingState) {
        mainMediaObject->pause();
    }
    else {
        if (mainMediaObject->currentSource().type() != MediaSource::Empty) {
           mainMediaObject->play();
        }
        else {
            qDebug("Playlist is empty!");
        }
    }
    updateSongPosition();
}


/// @brief Callback for previous button
void PlayerBar::handlePreviousButton() {
    emit previousButtonClicked();
}

/// @brief Callback for next button
void PlayerBar::handleNextButton() {
    emit nextButtonClicked();
}


/// @brief Callback for stop button
void PlayerBar::handleStopButton() {
    if (mainMediaObject->state() > Phonon::StoppedState) {
        resetDisplay();
        mainMediaObject->stop();
    }
}


/// @brief Update the song information in the bar
/// 
/// @param newSongInformation
void PlayerBar::updateSongInformation(QString newSongInformation) {
    qDebug("updateSongInformation: " + newSongInformation.toUtf8());
    currentSongInfo->setText(newSongInformation);
}

/// @brief Reset information to its initial state
void PlayerBar::resetDisplay() {
    qDebug("resetDisplay");
    currentSongPosition->setText(tr("--:--"));
    remainingSongPosition->setText(tr("--:--"));
    currentSongInfo->setText(tr(""));
}

/// @brief Commands to execute when the music ends
void PlayerBar::finish() {
    resetDisplay();
    mainMediaObject->stop();
}


/// @brief Quit application
void PlayerBar::exitApplication() {
    exit(0);
}
