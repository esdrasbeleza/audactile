#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <phonon/SeekSlider>
#include <phonon/VolumeSlider>


class PlayerBar : public QToolBar
{
public:
    PlayerBar();
};

#endif // PLAYERBAR_H
