#include "contextwidget.h"

ContextWidget::ContextWidget(QWidget *parent) : QWidget(parent)
{
    // Create widgets
    artistInfoWidget = new ArtistInfoWidget(this);
    lyricsWidget = new LyricsWidget(this);

    // Create a QButtonGroup where user will select artist, lyrics, etc.
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);

    // The amazing buttons
    QPushButton *artistButton = new QPushButton("Last.fm summary", this);
    QPushButton *lyricsButton = new QPushButton("Lyrics", this);

    artistButton->setIconSize(QSize(24, 24));
    artistButton->setCheckable(true);
    artistButton->setChecked(true);
    artistButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    lyricsButton->setCheckable(true);
    lyricsButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    buttonGroup->addButton(artistButton, 0);
    buttonGroup->addButton(lyricsButton, 1);

    // Stacked widget where we'll put artist info, lyrics, etc.
    QStackedWidget *contextContainer = new QStackedWidget(this);
    contextContainer->addWidget(artistInfoWidget);
    contextContainer->addWidget(lyricsWidget);

    // Connect buttons to container
    connect(buttonGroup, SIGNAL(buttonClicked(int)), contextContainer, SLOT(setCurrentIndex(int)));

    // The button group needs a layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(artistButton);
    buttonsLayout->addWidget(lyricsButton);
    buttonsLayout->setSpacing(5);
    buttonsLayout->setMargin(0);
    QWidget *buttonsWidget = new QWidget(this);
    buttonsWidget->setLayout(buttonsLayout);


    // Create layout
    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(buttonsWidget);
    vlayout->addWidget(contextContainer);
    this->setLayout(vlayout);

}

void ContextWidget::songInformationUpdated(QMap<QString, QString> newContextInformation) {
    artistInfoWidget->songInformationUpdated(newContextInformation);
}
