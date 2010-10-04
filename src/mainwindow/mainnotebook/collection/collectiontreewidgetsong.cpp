#include "collectiontreewidgetsong.h"
#include "collectiontreewidget.h"

CollectionTreeWidgetSong::CollectionTreeWidgetSong(Music *music, unsigned int id, QTreeWidget *parent)
    : CollectionTreeWidgetItem(CollectionTreeWidget::LevelMusic, id, parent)
{
    this->music = *music;

    // Set icon
    setIcon(0, IconFactory::fromTheme("sound"));
    setText(0, this->music.getTitle());
}

Music CollectionTreeWidgetSong::getMusic() {
    return music;
}

QList<QUrl> CollectionTreeWidgetSong::getUrlList() {
    QList<QUrl> urlList;
    urlList.append(music.getFileUrl());
    return urlList;
}
