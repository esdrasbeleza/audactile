#include <QToolButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "contextwidget.h"
#include "../../../settings/contextsettings.h"
#include "../../../separator.h"
#include "../../../iconfactory.h"

ContextWidget::ContextWidget(QWidget *parent) : QWidget(parent)
{
    // Create widgets
    artistInfoWidget = new ArtistInfoWidget(this);
    lyricsWidget = new LyricsWidget(this);

    // Create a QButtonGroup where user will select artist, lyrics, etc.
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);

    // The amazing buttons
    artistButton = new QPushButton("Last.fm summary", this);
    lyricsButton = new QPushButton("Lyrics", this);

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

    // Fetch button
    QToolButton *fetchButton = new QToolButton(this);
    fetchButton->setIcon(IconFactory::fromTheme("go-down"));
    fetchButton->setIconSize(QSize(24, 24));
    connect(fetchButton, SIGNAL(clicked()), this, SLOT(fetchButtonPressed()));

    // The button group needs a layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(artistButton);
    buttonsLayout->addWidget(lyricsButton);
    buttonsLayout->addWidget(Separator::verticalSeparator());
    buttonsLayout->addWidget(fetchButton);
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
    currentContext = newContextInformation;

    artistInfoWidget->resetLabels();
    lyricsWidget->resetLabels();

    if (ContextSettings::isFetchArtistInfoActive()) artistInfoWidget->songInformationUpdated(currentContext);
    if (ContextSettings::isFetchLyricsActive()) lyricsWidget->songInformationUpdated(currentContext);
}

void ContextWidget::fetchButtonPressed() {
    if (artistButton->isChecked()) artistInfoWidget->songInformationUpdated(currentContext);
    else if (lyricsButton->isChecked()) lyricsWidget->songInformationUpdated(currentContext);
}
