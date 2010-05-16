#ifndef MAINNOTEBOOK_H
#define MAINNOTEBOOK_H

#include <QTabWidget>
#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>
#include "filesystem/filesystemwidget.h"
#include "collection/collectiontreewidget.h"

class MainNotebook : public QTabWidget
{
public:
    MainNotebook(QWidget *parent);
};

#endif // MAINNOTEBOOK_H
