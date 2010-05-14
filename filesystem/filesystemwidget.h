#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QListView>
#include <QVBoxLayout>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <phonon/BackendCapabilities>


class FilesystemWidget : public QWidget
{
    Q_OBJECT

public:
    FilesystemWidget();

private slots:
    void updateWidget();
    void goUp();
    void goHome();    
    void pathChanged(QString newPath);
    void doubleClickAt(QModelIndex modelIndex);

private:
    QDir dir;
    QString startLocation;
    QFileSystemModel *fsWidgetModel;
    QListView *fsListView;
    QAction *goUpAction;
    QAction *goHomeAction;
    QStringList* getPhononExtensions();
};

#endif // FILESYSTEMWIDGET_H
