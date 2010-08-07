#ifndef SEPARATOR_H
#define SEPARATOR_H

#include <QFrame>

class Separator : public QFrame
{
public:
    Separator(QWidget *parent = NULL);
    static Separator *horizontalSeparator(QWidget *parent = NULL);
    static Separator *verticalSeparator(QWidget *parent = NULL);
};

#endif // SEPARATOR_H
