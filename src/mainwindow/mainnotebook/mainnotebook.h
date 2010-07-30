#ifndef MAINNOTEBOOK_H
#define MAINNOTEBOOK_H

#include <QTabWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include <QTabBar>
#include "../../settings/applicationsettings.h"
#include "../playlist/playlistwidget.h"
#include "filesystem/filesystemwidget.h"
#include "collection/collectiontreewidget.h"
#include "context/contextwidget.h"

class MainNotebook : public QTabWidget
{
Q_OBJECT

public:
    MainNotebook(QWidget *parent, PlaylistWidget *playlistWidget);

private slots:
    void saveTabOrder(int, int);

private:
    int collectionPosition;
    int contextPosition;
    int filesystemPosition;
    int playlistsPosition;

    // Widgets
    CollectionTreeWidget *collectionWidget;
    QWidget *contextContainer;
    FilesystemWidget *filesystemWidget;
    QLabel *testLabel3;

};

#endif // MAINNOTEBOOK_H
