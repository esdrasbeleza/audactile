#include "collectiontreewidgetsong.h"

CollectionTreeWidgetSong::CollectionTreeWidgetSong(Music *music, QTreeWidget *parent)
    : CollectionTreeWidgetItem(LevelMusic, parent)
{
    this->music = *music;

    qDebug("Music node created");
    // Set icon
    setIcon(0, IconFactory::fromTheme("sound"));
    setText(0, this->music.getTitle());

}

Music CollectionTreeWidgetSong::getMusic() {
    return music;
}

QList<QUrl> CollectionTreeWidgetSong::getUrlList() {
    qDebug("CollectionTreeWidgetSong getUrlList");

    QList<QUrl> urlList;
    urlList.append(music.getFileUrl());

    return urlList;
}
