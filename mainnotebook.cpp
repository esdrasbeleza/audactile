#include "mainnotebook.h"

MainNotebook::MainNotebook()
{
    setTabPosition(QTabWidget::West);


    // Widget of the Collection tab
    CollectionTreeWidget *collectionWidget = new CollectionTreeWidget();

    // Widget of the Files tab
    // TODO: put this into a separate class
    FilesystemWidget* filesystemWidget = new FilesystemWidget();


    // Creates a label test widget
    QLabel *testLabel2 = new QLabel(tr("Test label 2"));
    QLabel *testLabel3 = new QLabel(tr("Test label 3"));

    // Creates one tab.
    addTab(collectionWidget, tr("Collection"));
    addTab(filesystemWidget, tr("Files"));
    addTab(testLabel2, tr("Context"));
    addTab(testLabel3, tr("Playlists"));



    show();
}
