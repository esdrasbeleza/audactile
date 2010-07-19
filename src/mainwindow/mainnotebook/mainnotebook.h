#ifndef MAINNOTEBOOK_H
#define MAINNOTEBOOK_H

#include <QTabWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include "../playlist/playlistwidget.h"
#include "filesystem/filesystemwidget.h"
#include "collection/collectiontreewidget.h"
#include "context/contextwidget.h"

class MainNotebook : public QTabWidget
{
public:
    MainNotebook(QWidget *parent, PlaylistWidget *playlistWidget);
};

#endif // MAINNOTEBOOK_H
