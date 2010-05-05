#include "playerbar.h"

PlayerBar::PlayerBar()
{
    setAllowedAreas(Qt::TopToolBarArea|Qt::BottomToolBarArea);
    setIconSize(QSize(36, 36));

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
