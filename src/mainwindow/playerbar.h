#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <cmath>
#include <phonon/MediaObject>
#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>


using namespace Phonon;

class PlayerBar : public QToolBar
{
    Q_OBJECT

public:
    PlayerBar(QWidget *parent, Phonon::MediaObject *mediaObject, Phonon::AudioOutput *audioOutput);

public slots:
    void updateSongPosition();
    void updateSongInformation(QString newSongInformation);
    void handleState(Phonon::State oldState, Phonon::State newState);
    void handlePlayButton();
    void handleStopButton();
    void handleNextButton();
    void handlePreviousButton();
    void finish();

signals:
    void nextButtonClicked();
    void previousButtonClicked();

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

    void resetDisplay();

};

#endif // PLAYERBAR_H
