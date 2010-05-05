#include "playerbar.h"

PlayerBar::PlayerBar()
{
    QToolButton* playButton = new QToolButton();
    QToolButton* pauseButton = new QToolButton();
    QToolButton* exitButton = new QToolButton();

    playButton->setIcon(QIcon::fromTheme("player_play"));
    pauseButton->setIcon(QIcon::fromTheme("player_pause"));
    exitButton->setIcon(QIcon::fromTheme("exit"));

    addWidget(playButton);
    addWidget(pauseButton);
    addSeparator();
    addWidget(exitButton);

    show();
}
