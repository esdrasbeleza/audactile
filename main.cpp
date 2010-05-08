#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Player");
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
