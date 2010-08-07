#include "mainnotebook.h"

/// @brief Construtor
/// 
/// @param parent Parent widget
MainNotebook::MainNotebook(QWidget *parent, PlaylistWidget *playlistWidget)
{
    setParent(parent);
    setTabPosition(QTabWidget::West);

    // Set tabs movable
    setMovable(true);
    QTabBar *tabbar = tabBar();
    connect(tabbar, SIGNAL(tabMoved(int,int)), this, SLOT(saveTabOrder(int,int)));

    // Widget of the Collection tab
    collectionWidget = new CollectionTreeWidget();

    // Widget of the Files tab
    filesystemWidget = new FilesystemWidget(this);
    connect(filesystemWidget, SIGNAL(askToAddItemToPlaylist(PlaylistItem*)), playlistWidget, SLOT(addSong(PlaylistItem*)));


    // Widget of the Context tab
    ContextWidget *contextWidget = new ContextWidget(this);
    connect(playlistWidget, SIGNAL(songInformationUpdated(QMap<QString,QString>)), contextWidget, SLOT(songInformationUpdated(QMap<QString,QString>)));

    contextContainer = new QWidget(this);
    QVBoxLayout *contextLayout = new QVBoxLayout(contextContainer);
    contextLayout->setContentsMargins(5, 5, 5, 5);
    contextLayout->addWidget(contextWidget);

    // Playlists widget
    testLabel3 = new QLabel(tr("Test label 3"));

    // Set positions
    collectionPosition = (ApplicationSettings::getTabOrder("collection") > -1) ? ApplicationSettings::getTabOrder("collection") : 0;
    filesystemPosition = (ApplicationSettings::getTabOrder("filesystem") > -1) ? ApplicationSettings::getTabOrder("filesystem") : 1;
    contextPosition    = (ApplicationSettings::getTabOrder("context")    > -1) ? ApplicationSettings::getTabOrder("context")    : 2;
    playlistsPosition  = (ApplicationSettings::getTabOrder("playlists")  > -1) ? ApplicationSettings::getTabOrder("playlists")  : 3;


    // Insert tabs
    for (int i = 0; i < 4; i++) {
        if (i == collectionPosition) { addTab(collectionWidget, IconFactory::fromTheme("audio-x-generic"), tr("Collection")); }
        else if (i == filesystemPosition) { addTab(filesystemWidget, IconFactory::fromTheme("system-file-manager"), tr("Files")); }
        else if (i == contextPosition) { addTab(contextContainer, IconFactory::fromTheme("emblem-web"), tr("Context")); }
        else if (i == playlistsPosition) { addTab(testLabel3, IconFactory::fromTheme("text-x-generic"), tr("Playlists")); }
    }

    show();
}

void MainNotebook::saveTabOrder(int from, int to) {

    for (int i = 0; i < count(); i++) {
        if (widget(i) == collectionWidget) collectionPosition = i;
        else if (widget(i) == filesystemWidget) filesystemPosition = i;
        else if (widget(i) == contextContainer) contextPosition = i;
        else if (widget(i) == testLabel3) playlistsPosition = i;
    }

    ApplicationSettings::setTabOrder("collection", collectionPosition);
    ApplicationSettings::setTabOrder("filesystem", filesystemPosition);
    ApplicationSettings::setTabOrder("context", contextPosition);
    ApplicationSettings::setTabOrder("playlists", playlistsPosition);

}
