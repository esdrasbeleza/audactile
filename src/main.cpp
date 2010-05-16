#include <QtGui/QApplication>
#include "mainwindow/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("BlzAmp");
    a.setApplicationVersion("0.1");

    MainWindow w;
    w.showMaximized();
    return a.exec();
}

