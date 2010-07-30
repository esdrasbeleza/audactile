#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QListView>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QLineEdit>
#include <QLabel>
#include "../../../iconfactory.h"
//#include "../../mainwindow.h"
#include "../../playlist/playlistitem.h"
#include "../../../iconfactory.h"


class FilesystemWidget : public QWidget
{
    Q_OBJECT

public:
    FilesystemWidget(QWidget *parent);

private slots:
    void updateWidget();
    void goUp();
    void goHome();    
    void pathChanged(QString newPath);
    void doubleClickAt(QModelIndex modelIndex);
    void setNameFilter(QString filter);

signals:
    void askToAddItemToPlaylist(PlaylistItem*);

private:
    QDir dir;
    QString startLocation;
    QFileSystemModel *fsWidgetModel;
    QListView *fsListView;
    QAction *goUpAction;
    QAction *goHomeAction;
    QLineEdit* filterEdit;
    void setNameFilter();
};

#endif // FILESYSTEMWIDGET_H
