#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <phonon/MediaObject>
#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>


class PlayerBar : public QToolBar
{
    Q_OBJECT

public:
    PlayerBar(QWidget *parent, Phonon::MediaObject *mediaObject);

public slots:
    void tick();

private:
    Phonon::MediaObject *mainMediaObject;
    QLabel *currentSongPosition;
    QLabel *remainingSongPosition;
};

#endif // PLAYERBAR_H
