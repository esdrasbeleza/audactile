#include "mainnotebook.h"

/// @brief Construtor
/// 
/// @param parent Parent widget
MainNotebook::MainNotebook(QWidget *parent, PlaylistWidget *playlistWidget)
{
    setParent(parent);
    setTabPosition(QTabWidget::West);

    // Widget of the Collection tab
    CollectionTreeWidget *collectionWidget = new CollectionTreeWidget();

    // Widget of the Files tab
    FilesystemWidget *filesystemWidget = new FilesystemWidget(this);

    // Widget of the Context tab
    ContextWidget *contextWidget = new ContextWidget(this);
    connect(playlistWidget, SIGNAL(songInformationUpdated(QMap<QString,QString>)), contextWidget, SLOT(songInformationUpdated(QMap<QString,QString>)));

    QWidget *contextContainer = new QWidget(this);
    QVBoxLayout *contextLayout = new QVBoxLayout(contextContainer);
    contextLayout->setContentsMargins(16, 16, 16, 16);
    contextLayout->addWidget(contextWidget);

    // Playlists widget
    QLabel *testLabel3 = new QLabel(tr("Test label 3"));

    // Creates one tab.
    addTab(collectionWidget, QIcon::fromTheme("audio-x-generic"), tr("Collection"));
    addTab(filesystemWidget, QIcon::fromTheme("system-file-manager"), tr("Files"));
    addTab(contextContainer, QIcon::fromTheme("emblem-web"), tr("Context"));
    addTab(testLabel3, QIcon::fromTheme("text-x-generic"), tr("Playlists"));

    show();
}
