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
    collectionDb->addArtist("Artist 1");
    collectionDb->addArtist("Artist 2");
    collectionDb->addArtist("Artist 3");

    collectionDb->addAlbum("Artist 1", "Album 1 of Artist 1");
    collectionDb->addAlbum("Artist 2", "Album 2 of Artist 1");
    collectionDb->addAlbum("Artist 2", "Album 1 of Artist 2");
    collectionDb->addAlbum("Artist 2", "Album 1 of Artist 2");

    Music *music = new Music(QUrl("file:///tmp/teste.mp3"));
    collectionDb->addMusic(music);

    MainWindow w;
    w.showMaximized();
    return a.exec();
}

