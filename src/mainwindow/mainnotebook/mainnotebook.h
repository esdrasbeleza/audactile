#ifndef MAINNOTEBOOK_H
#define MAINNOTEBOOK_H

#include <QTabWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include <QTabBar>
#include "QProgressBar"
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
    void saveTabOrder();
    void showCollectionProgress(); // TODO: put this in a better place
    void hideCollectionProgress(); // TODO: put this in a better place

private:
    int collectionPosition;
    int contextPosition;
    int filesystemPosition;
    int playlistsPosition;

    // Collection progressbar -- TODO: put this in a better place
    QWidget *progressContainer;
    QProgressBar *scanProgress;
    QLabel *scanLabel;

    // Widgets
    CollectionTreeWidget *collectionWidget;
    QWidget *collectionContainer;
    QWidget *contextContainer;
    QWidget *filesystemContainer;
    QLabel *testLabel3;

};

#endif // MAINNOTEBOOK_H
