#ifndef MAINNOTEBOOK_H
#define MAINNOTEBOOK_H

#include <QDebug>
#include <QTabWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include <QListView>
#include <QFileSystemModel>
#include <QDesktopServices>
#include "widgets/collectiontreewidget.h"

class MainNotebook : public QTabWidget
{
public:
    MainNotebook();
};

#endif // MAINNOTEBOOK_H
