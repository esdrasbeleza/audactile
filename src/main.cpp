#include <QtGui/QApplication>
#include "mainwindow/mainwindow.h"
#include "settings/applicationsettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Audactile");
    a.setApplicationName("Audactile");
    a.setApplicationVersion("0.1");

    // Read and/or set application settings
    ApplicationSettings::createAppDirIfNeeded();
    ApplicationSettings::initialisation();

    MainWindow w;
    w.showMaximized();
    return a.exec();
}

