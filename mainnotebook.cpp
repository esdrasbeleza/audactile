#include "mainnotebook.h"

MainNotebook::MainNotebook()
{
    setTabPosition(QTabWidget::West);


    CollectionTreeWidget *collectionWidget = new CollectionTreeWidget();

    // Creates a label test widget
    QLabel *testLabel2 = new QLabel(tr("Test label 2"));
    QLabel *testLabel3 = new QLabel(tr("Test label 3"));

    // Creates one tab.
    addTab(collectionWidget, tr("Collection"));
    addTab(testLabel2, tr("Context"));
    addTab(testLabel3, tr("Playlists"));


    show();
}
