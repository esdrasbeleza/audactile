#include "abstractcontainer.h"

AbstractContainer::AbstractContainer(QWidget *parent) :
    QFrame(parent)
{
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Sunken);

    contentView = new QWebView(this);

    // Stole font from a QLabel
    QLabel *label = new QLabel("I will die soon!");
    QFont font = label->font();
    delete label;

    // TODO: set margins, color, etc.
    header= "<div style=\"font-family: " + font.family() + "; \">";
    footer = "</div>";

    qDebug("HEADER: " + header.toUtf8());

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
