#include "artistinfowidget.h"

// TODO: put a "fetch info" and "reload" buttons.
// TODO: show a message when no information is available.
ArtistInfoWidget::ArtistInfoWidget(QWidget *parent) :
    AbstractContainer(parent)
{
    context = new LastFmContext(this);
    connect(context, SIGNAL(contextUpdated(QMap<QString,QString>)), this, SLOT(updateContextInformation(QMap<QString,QString>)));

    resetLabels();
}

void ArtistInfoWidget::songInformationUpdated(QMap<QString, QString> newContextInformation) {
    lastRequest = newContextInformation;
    QString html("<div class=\"title\">" + newContextInformation.value("artist") + "</div>");
    setHtml(html);
    context->getInfo(newContextInformation.value("artist"));
}

void ArtistInfoWidget::updateContextInformation(QMap<QString, QString>newContextInformation) {
    QString artist = newContextInformation.value("artist");
    if (artist.toLower() != lastRequest.value("artist").toLower()) return;

    QString html = "<div class=\"title\">" + artist + "</div>";
    if (!newContextInformation.value("picture").isEmpty()) {
        html += "<p align=\"center\"><img src=\"" + newContextInformation.value("picture") + "\"></p>";
    }
    html += "<p>" + newContextInformation.value("summary") + "</p>";
    html += "<div class=\"reference\"><a href=\"" + newContextInformation.value("profile") + "\">More...</a></div>";
    setHtml(html);
}

void ArtistInfoWidget::resetLabels() {
    setHtml("<div class=\"title\">No music being listened!</div>");
}
