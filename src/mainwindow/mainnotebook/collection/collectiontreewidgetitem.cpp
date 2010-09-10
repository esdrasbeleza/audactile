#include "collectiontreewidgetitem.h"

CollectionTreeWidgetItem::CollectionTreeWidgetItem(Music *music, QTreeWidget *parent) :
    QTreeWidgetItem(parent, 0)
{
    this->music = music;

    // Set icon
    setIcon(0, IconFactory::fromTheme("sound"));
    setText(0, this->music.getTitle());
}

Music CollectionTreeWidgetItem::getMusic() {
    return music;
}
