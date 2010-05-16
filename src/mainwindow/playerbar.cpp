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



    // Vertical box with slider and current song time labels
    QFrame *songPositionWidget = new QFrame(this);
    songPositionWidget->setFrameShadow(QFrame::Sunken);
    songPositionWidget->setFrameShape(QFrame::StyledPanel);
    songPositionWidget->setMidLineWidth(4);
    
    // Set background for song position widget
    QPalette palette = songPositionWidget->palette();
    QLinearGradient songPositionBgGradient(0, 0, 0, songPositionLabelsWidget->height());
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
    int secs, mins;
    QString qStr;

    qint64 rem = mainMediaObject->remainingTime();
    if (rem > 0) {
        songPositionSlider->setEnabled(true);

        secs = (rem / 1000) % 60;
        mins = (rem / 1000) / 60;
        remainingSongPosition->setText("-" + QString::number(mins) + ":" + qStr.sprintf("%02d", secs));


        qint64 cur = mainMediaObject->currentTime();
        secs = (cur / 1000) % 60;
        mins = (cur / 1000) / 60;
        currentSongPosition->setText(QString::number(mins) + ":" + qStr.sprintf("%02d", secs));
    }
    else {
        resetPosition();
    }
}

void PlayerBar::resetPosition() {
    currentSongPosition->setText(tr("--:--"));
    remainingSongPosition->setText(tr("--:--"));
    currentSongInfo->clear();
    songPositionSlider->setDisabled(true);
}


void PlayerBar::updateSongInformation(QString newSongInformation) {
    currentSongInfo->setText(newSongInformation);
}
