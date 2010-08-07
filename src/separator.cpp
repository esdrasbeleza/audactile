#include "separator.h"

Separator::Separator(QWidget *parent) : QFrame(parent)
{
}


Separator *Separator::horizontalSeparator(QWidget *parent) {
    Separator *separator = new Separator(parent);
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    return separator;
}

Separator *Separator::verticalSeparator(QWidget *parent) {
    Separator *separator = new Separator(parent);
    separator->setFrameShape(QFrame::VLine);
    separator->setFrameShadow(QFrame::Sunken);
    return separator;
}
