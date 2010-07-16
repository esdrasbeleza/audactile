#ifndef ICONFACTORY_H
#define ICONFACTORY_H

#include <QObject>
#include <QIcon>
#include <QStyle>

class IconFactory : public QObject
{

public:
    static QIcon fromTheme(QString iconName);


};

#endif // ICONFACTORY_H
