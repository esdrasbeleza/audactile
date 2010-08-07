#include "lyricswidget.h"

LyricsWidget::LyricsWidget(QWidget *parent) : QWidget(parent)
{
    QLabel *label = new QLabel("Here will be the lyrics");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);

    setLayout(layout);
}
