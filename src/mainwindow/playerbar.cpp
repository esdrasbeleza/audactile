#include "playerbar.h"

using namespace Phonon;

PlayerBar::PlayerBar(QWidget *parent, Phonon::MediaObject *mediaObject)
{
    setAllowedAreas(Qt::TopToolBarArea|Qt::BottomToolBarArea);
    setIconSize(QSize(36, 36));

    mainMediaObject = mediaObject;

    // Buttons
    QToolButton *playButton = new QToolButton();
    QToolButton *stopButton = new QToolButton();
    QToolButton *exitButton = new QToolButton();
    QToolButton *nextButton = new QToolButton();
    QToolButton *prevButton = new QToolButton();
    QToolButton *prefButton = new QToolButton();

    playButton->setIcon(QIcon::fromTheme("media-playback-start"));
    stopButton->setIcon(QIcon::fromTheme("media-playback-stop"));
    nextButton->setIcon(QIcon::fromTheme("media-skip-forward"));
    prevButton->setIcon(QIcon::fromTheme("media-skip-backward"));
    prefButton->setIcon(QIcon::fromTheme("preferences-other"));
    exitButton->setIcon(QIcon::fromTheme("exit"));

    // Horizontal box with current song position labels
    QWidget *songPositionLabelsWidget = new QWidget(this);
    QHBoxLayout *songPositionLabelsHBox = new QHBoxLayout(this);
    currentSongPosition = new QLabel(tr("--:--"));
    remainingSongPosition = new QLabel(tr("--:--"));
    songPositionLabelsHBox->addWidget(currentSongPosition, 1, Qt::AlignLeft);
    songPositionLabelsHBox->addWidget(remainingSongPosition, 1, Qt::AlignRight);
    songPositionLabelsWidget->setLayout(songPositionLabelsHBox);



    // Vertical box with slider and current song time labels
    QWidget *songPositionWidget = new QWidget(this);
    QVBoxLayout *songPositionVBox = new QVBoxLayout(this);
    SeekSlider *songPositionSlider = new SeekSlider(mainMediaObject, this);
    songPositionSlider->setOrientation(Qt::Horizontal);
    songPositionVBox->addWidget(songPositionLabelsWidget);
    songPositionVBox->addWidget(songPositionSlider);
    songPositionWidget->setLayout(songPositionVBox);

    // Volume button
    QToolButton *volumeSliderButton = new QToolButton(this);
    volumeSliderButton->setIcon(QIcon::fromTheme("audio-volume-high"));

    addWidget(playButton);
    addWidget(stopButton);
    addSeparator();
    addWidget(prevButton);
    addWidget(nextButton);
    addSeparator();
    addWidget(songPositionWidget);
    addSeparator();
    addWidget(prefButton);
    addWidget(volumeSliderButton);
    addSeparator();
    addWidget(exitButton);

    show();
}



void PlayerBar::tick() {
    qDebug("tick");
    currentSongPosition->setText(QString((int)(mainMediaObject->currentTime()/1000)));
    remainingSongPosition->setText(QString((int)(mainMediaObject->remainingTime()/1000)));
}
