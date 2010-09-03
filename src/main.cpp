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
//    CollectionDatabase *collectionDb = new CollectionDatabase();

//    For test purposes
//    collectionDb->addMusic("/tmp/test1.mp3");
//    collectionDb->addMusic("/tmp/test2.mp3");
//    collectionDb->addMusic("/tmp/test3.mp3");
//    collectionDb->addMusic("/tmp/test4.mp3");
//    collectionDb->addMusic("/tmp/test5.mp3");

    // For test purpose, try to scan the folders and generate the database
    service->scan();



    MainWindow w;
    w.showMaximized();
    return a.exec();
}

