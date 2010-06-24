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
    addTab(collectionWidget, QIcon::fromTheme("audio-x-generic"), tr("Collection"));
    addTab(filesystemWidget, QIcon::fromTheme("system-file-manager"), tr("Files"));
    addTab(testLabel2, QIcon::fromTheme("emblem-web"), tr("Context"));
    addTab(testLabel3, QIcon::fromTheme("text-x-generic"), tr("Playlists"));

    show();
}
