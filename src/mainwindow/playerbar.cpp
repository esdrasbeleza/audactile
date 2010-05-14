#include "playerbar.h"

using namespace Phonon;

PlayerBar::PlayerBar()
{
    setAllowedAreas(Qt::TopToolBarArea|Qt::BottomToolBarArea);
    setIconSize(QSize(36, 36));

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
    QWidget *songPositionLabelsWidget = new QWidget();
    QHBoxLayout *songPositionLabelsHBox = new QHBoxLayout();
    QLabel *currentSongPosition = new QLabel(tr("--:--"));
    QLabel *pendingSongPosition = new QLabel(tr("--:--"));
    songPositionLabelsHBox->addWidget(currentSongPosition, 1, Qt::AlignLeft);
    songPositionLabelsHBox->addWidget(pendingSongPosition, 1, Qt::AlignRight);
    songPositionLabelsWidget->setLayout(songPositionLabelsHBox);



    // Vertical box with slider and current song time labels
    QWidget *songPositionWidget = new QWidget();
    QVBoxLayout *songPositionVBox = new QVBoxLayout();
    SeekSlider *songPositionSlider = new SeekSlider();
    songPositionSlider->setOrientation(Qt::Horizontal);
    songPositionVBox->addWidget(songPositionLabelsWidget);
    songPositionVBox->addWidget(songPositionSlider);
    songPositionWidget->setLayout(songPositionVBox);

    // Volume button
    QToolButton *volumeSliderButton = new QToolButton();
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
