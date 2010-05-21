#include "mainnotebook.h"

/// @brief Construtor
/// 
/// @param parent Parent widget
MainNotebook::MainNotebook(QWidget *parent)
{
    setParent(parent);
    setTabPosition(QTabWidget::West);

    // Widget of the Collection tab
    CollectionTreeWidget *collectionWidget = new CollectionTreeWidget();

    // Widget of the Files tab
    FilesystemWidget *filesystemWidget = new FilesystemWidget(this);


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
