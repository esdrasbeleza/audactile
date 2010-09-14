#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QApplication>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <cmath>
#include <phonon/MediaObject>
#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>
#include "../separator.h"
#include "../iconfactory.h"
#include "../settings/settingsdialog/settingsdialog.h"


using namespace Phonon;

class PlayerBar : public QWidget
{
    Q_OBJECT

public:
    PlayerBar(QWidget *parent, Phonon::MediaObject *mediaObject, Phonon::AudioOutput *audioOutput);

public slots:
    void updateSongPosition();
    void updateSongInformation(QMap<QString,QString> newSongInformation);
    void handleState(Phonon::State newState);
    void handlePlayButton();
    void handleWindowStateChange(Qt::WindowStates windowState);
    void handleStopButton();
    void exitApplication();
    void openSettings();
    void finish();

signals:
    void nextButtonClicked();
    void previousButtonClicked();
    void toggleFullScreen();

private:
    Phonon::MediaObject *mainMediaObject;
    Phonon::AudioOutput *audioOutput;
    QLabel *currentSongPosition;
    QLabel *remainingSongPosition;
    QLabel *currentSongInfo;
    SeekSlider *songPositionSlider;

    QToolButton *playButton;
    QToolButton *stopButton;
    QToolButton *exitButton;
    QToolButton *nextButton;
    QToolButton *previousButton;
    QToolButton *prefButton;
    QToolButton *fullScreenButton;

    void resetDisplay();

};

#endif // PLAYERBAR_H
