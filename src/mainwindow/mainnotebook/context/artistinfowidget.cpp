#include "artistinfowidget.h"

// TODO: put a "fetch info" and "reload" buttons.
// TODO: show a message when no information is available.
ArtistInfoWidget::ArtistInfoWidget(QWidget *parent) :
    QScrollArea(parent)
{
    context = new LastFmContext(this);
    connect(context, SIGNAL(contextUpdated(QMap<QString,QString>)), this, SLOT(updateContextInformation(QMap<QString,QString>)));

    setFrameShape(QFrame::Box);

    // Set background and foreground colors
    QWidget *widget = new QWidget(this);
    QPalette contextPalette = widget->palette();
    contextPalette.setColor(backgroundRole(), QColor(255,255, 255));
    contextPalette.setColor(foregroundRole(), QColor(100,100,100));
    widget->setPalette(contextPalette);
    widget->setAutoFillBackground(true);

    artistLabel = new QLabel(this);
    artistLabel->setWordWrap(true);
    QFont artistFont = artistLabel->font();
    artistFont.setBold(true);
    artistFont.setPointSize(artistFont.pointSize() + 4);
    artistLabel->setFont(artistFont);
    artistLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);

    pictureLabel = new QLabel(this);

    summaryLabel = new QLabel(this);
    summaryLabel->setOpenExternalLinks(true);
    summaryLabel->setWordWrap(true);
    QFont summaryFont = summaryLabel->font();
    summaryFont.setPointSize(summaryFont.pointSize() + 2);
    summaryLabel->setFont(summaryFont);
    summaryLabel->setTextInteractionFlags(Qt::TextBrowserInteraction | Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    summaryLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Maximum);

    moreLinkLabel = new QLabel(this);
    QFont moreLinkFont = moreLinkLabel->font();
    moreLinkFont.setItalic(true);
    moreLinkLabel->setFont(moreLinkFont);
    moreLinkLabel->setOpenExternalLinks(true);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->addWidget(artistLabel, 0, Qt::AlignTop);
    layout->addSpacing(20);
    layout->addWidget(pictureLabel, 0, Qt::AlignTop | Qt::AlignHCenter);
    layout->addSpacing(20);
    layout->addWidget(summaryLabel, 0, Qt::AlignTop);
    layout->addSpacing(20);
    layout->addWidget(moreLinkLabel, 0, Qt::AlignTop | Qt::AlignRight);
    layout->addStretch(0);
    widget->setLayout(layout);
    setWidget(widget);
    setWidgetResizable(true);
    resetLabels();


}

void ArtistInfoWidget::songInformationUpdated(QMap<QString, QString> newContextInformation) {
    lastRequest = newContextInformation;
    artistLabel->setText(newContextInformation.value("artist"));
    context->getInfo(newContextInformation.value("artist"));
}

void ArtistInfoWidget::updateContextInformation(QMap<QString, QString>newContextInformation) {
    QString artist = newContextInformation.value("artist");
    if (artist.toLower() != lastRequest.value("artist").toLower()) return;

    artistLabel->setText(artist);
    summaryLabel->setText(newContextInformation.value("summary"));
    moreLinkLabel->setText("<a href=\"" + newContextInformation.value("profile") + "\">More...</a>");
    pictureLabel->setText("Loading...");

    if (!newContextInformation.value("picture").isEmpty()) {
       pictureBuffer = new QBuffer(this);
       pictureBuffer->open(QIODevice::WriteOnly);

       QUrl pictureUrl(newContextInformation.value("picture"));
       QNetworkRequest netRequest;
       QNetworkAccessManager *netManager = new QNetworkAccessManager(this);
       netRequest.setUrl(pictureUrl);
       qDebug("Picture: " + newContextInformation.value("picture").toUtf8());
       contextReply = netManager->get(netRequest);
       connect(contextReply, SIGNAL(readyRead()), this, SLOT(readPictureReply())); // TODO: handle error() signal
       connect(contextReply, SIGNAL(finished()), this, SLOT(showPicture())); // TODO: handle error() signal
    }

}

void ArtistInfoWidget::readPictureReply() {
    pictureBuffer->write(contextReply->readAll());
}

void ArtistInfoWidget::showPicture() {
    pictureData.loadFromData(pictureBuffer->data());
    QPixmap pixmap = QPixmap::fromImage(pictureData);
    pictureLabel->setPixmap(pixmap);
    pictureLabel->setMinimumSize(pixmap.size());
}

void ArtistInfoWidget::resetLabels() {
    artistLabel->setText("<b>No music being listened!</b>");
    summaryLabel->clear();
    pictureLabel->clear();
    moreLinkLabel->clear();
}
