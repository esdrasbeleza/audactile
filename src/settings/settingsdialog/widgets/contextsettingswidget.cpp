#include "contextsettingswidget.h"

ContextSettingsWidget::ContextSettingsWidget(QWidget *parent) :
    QWidget(parent)
{
    // Create checkboxes
    fetchSummary = new QCheckBox("Fetch artist summary from Last.fm automatically");
    fetchLyrics  = new QCheckBox("Fetch lyrics from LyricWiki automatically");

    // Set their default value
    fetchSummary->setChecked(ContextSettings::isFetchArtistInfoActive());
    fetchLyrics->setChecked(ContextSettings::isFetchLyricsActive());

    // Add them into a layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(fetchSummary);
    layout->addWidget(fetchLyrics);
    layout->addStretch(0);

    setLayout(layout);
}

void ContextSettingsWidget::applySettings() {
    ContextSettings::setFetchArtistInfoActive(fetchSummary->isChecked());
    ContextSettings::setFetchLyricsActive(fetchLyrics->isChecked());
}
