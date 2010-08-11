#include "abstractcontainer.h"

AbstractContainer::AbstractContainer(QWidget *parent) :
    QFrame(parent)
{
    setFrameShape(QFrame::Box);
    setFrameShadow(QFrame::Sunken);
    setContentsMargins(0, 0, 0, 0);

    contentView = new QWebView(this);
    // TODO: open links in another window

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(contentView);

    setLayout(layout);
}

void AbstractContainer::setHtml(QString html) {
    contentView->setHtml(html);
}
