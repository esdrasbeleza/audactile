#include "collectiontreewidgetitem.h"
#include "collectiontreewidget.h"

CollectionTreeWidgetItem::CollectionTreeWidgetItem(unsigned int level, unsigned int id, QTreeWidget *parent) :
    QTreeWidgetItem(parent, 0)
{
    this->level = level;
    this->id = id;
}

unsigned int CollectionTreeWidgetItem::getNodeLevel() {
    return level;
}

unsigned int CollectionTreeWidgetItem::getId() {
    return id;
}

QList<QUrl> CollectionTreeWidgetItem::getUrlList(QSqlTableModel *collectionModel) {
    QList<QUrl> urlList;

    QString idType;
    if (level == CollectionTreeWidget::LevelArtist) {
        idType = "id_artist";
    }
    else if (level == CollectionTreeWidget::LevelAlbum) {
        idType = "id_album";
    }
    else if (level == CollectionTreeWidget::LevelMusic) {
        idType = "id_music";
    }
    collectionModel->setFilter(idType + " = " + QString::number(id));
    collectionModel->select();

    while (collectionModel->canFetchMore()) collectionModel->fetchMore();
    int total = collectionModel->rowCount();

    for (int i = 0; i < total; i++) {
        QString path = collectionModel->record(i).value(collectionModel->fieldIndex("path")).toString();
        QUrl url(path);
        urlList.append(url);
    }

    return urlList;
}
