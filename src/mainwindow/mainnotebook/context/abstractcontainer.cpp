#include "abstractcontainer.h"

AbstractContainer::AbstractContainer(QWidget *parent) :
    QFrame(parent)
{
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Sunken);

    contentView = new QWebView(this);
    connect(contentView, SIGNAL(linkClicked(QUrl)), this, SLOT(openLinksInExternalWindow(QUrl)));
    contentView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    contentView->setContextMenuPolicy(Qt::NoContextMenu);

    // Stole font from a QLabel
    QLabel *label = new QLabel("I will die soon!");
    QFont font = label->font();
    delete label;

    // TODO: set margins, color, etc.
    QStringList headerList;
    headerList += "<style type=\"text/css\">body { \n";
    headerList += "  font-family: " + font.family() + ";\n";
    headerList += " font-size: " + QString::number(font.pointSize() + 2) + "pt; \n";
    headerList += "} \n";
    headerList += ".title {";
    headerList += " font-size: " + QString::number(font.pointSize() + 4) + "pt; \n";
    headerList += " font-weight: bold; \n";
    headerList += "}\n";
    headerList += ".reference {";
    headerList += " text-align: right;";
    headerList += " font-style: italic; \n";
    headerList += "}\n";
    headerList += "</style>";

    header = headerList.join("");

    footer = ""; // no footer yet.


    // TODO: open links in another window
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(contentView);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);
}

void AbstractContainer::setHtml(QString html) {
    html = header + html + footer;
    contentView->setHtml(html);
}

void AbstractContainer::openLinksInExternalWindow(QUrl url) {
    QDesktopServices::openUrl(url);
}
