#ifndef MAINNOTEBOOK_H
#define MAINNOTEBOOK_H

#include <QTabWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include "widgets/filesystemwidget.h"
#include "widgets/collectiontreewidget.h"

class MainNotebook : public QTabWidget
{
public:
    MainNotebook();
};

#endif // MAINNOTEBOOK_H
