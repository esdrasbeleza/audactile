#include "contextwidget.h"

ContextWidget::ContextWidget(QWidget *parent) :
    QWidget(parent)
{
    context = new LastFmContext(this);
    connect(context, SIGNAL(contextUpdated(QMap<QString,QString>)), this, SLOT(updateContextInformation(QMap<QString,QString>)));

    artistLabel = new QLabel(this);
    pictureLabel = new QLabel(this);
    summaryLabel = new QLabel(this);
    summaryLabel->setOpenExternalLinks(true);
    summaryLabel->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(artistLabel);
    layout->addWidget(summaryLabel);
    setLayout(layout);
    resetLabels();
}

void ContextWidget::songInformationUpdated(QMap<QString, QString> newContextInformation) {
    lastRequest = newContextInformation;
    context->getInfo(newContextInformation.value("artist"));
}

void ContextWidget::updateContextInformation(QMap<QString, QString>newContextInformation) {
    QString artist = newContextInformation.value("artist");
    if (artist.toLower() != lastRequest.value("artist").toLower()) return;

    artistLabel->setText("<b>" + artist + "</b>");
    summaryLabel->setText(newContextInformation.value("summary"));


    // TODO: LOAD PICTURE
    // http://lists.trolltech.com/qt-interest/2006-03/thread01519-0.html
    // http://www.greyc.ensicaen.fr/ensicaen/Docs/Qt4/widgets-imageviewer.html
}

void ContextWidget::resetLabels() {
    artistLabel->setText("<b>No music being listened!</b>");
    summaryLabel->clear();
    pictureLabel->clear();
}
