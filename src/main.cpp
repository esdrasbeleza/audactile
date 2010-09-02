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
    collectionDb->addMusic("/tmp/teste1.mp3");
    collectionDb->addMusic("/tmp/teste2.mp3");
    collectionDb->addMusic("/tmp/teste3.mp3");
    collectionDb->addMusic("/tmp/teste4.mp3");
    collectionDb->addMusic("/tmp/teste5.mp3");




    MainWindow w;
    w.showMaximized();
    return a.exec();
}

