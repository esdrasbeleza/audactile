#include <QtGui/QApplication>
#include "mainwindow/mainwindow.h"
#include "settings/applicationsettings.h"
#include "services/collectionservice.h"
#include "collection/collectiondatabase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Audactile");
    a.setApplicationName("Audactile");
    a.setApplicationVersion("0.1");

    // Read and/or set application settings
    ApplicationSettings::createAppDirIfNeeded();
    ApplicationSettings::initialisation();

    // Start collection service
    CollectionService *service = new CollectionService();

    // Test collection database
    CollectionDatabase *collectionDb = new CollectionDatabase();


    MainWindow w;
    w.showMaximized();
    return a.exec();
}

