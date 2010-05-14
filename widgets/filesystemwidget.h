#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QListView>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QToolBar>
#include <QToolButton>
#include <QAction>

class FilesystemWidget : public QWidget
{
    Q_OBJECT

public:
    FilesystemWidget();

private slots:
    void goUp();

private:
    QDir dir;
    QString startLocation;
    QFileSystemModel *fsWidgetModel;
    QListView *fsListView;

    QAction* goUpAction;
};

#endif // FILESYSTEMWIDGET_H
