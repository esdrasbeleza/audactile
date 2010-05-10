#include "filesystemwidget.h"

FilesystemWidget::FilesystemWidget()
{
    QDir dir;
    QString musicLocation = QDesktopServices::storageLocation(QDesktopServices::MusicLocation);
    if (musicLocation.isEmpty() || !dir.exists(musicLocation)) { musicLocation = QDir::homePath(); }

    QFileSystemModel *fsWidgetModel = new QFileSystemModel();
    fsWidgetModel->setRootPath(musicLocation);
    setModel(fsWidgetModel);
    setRootIndex(fsWidgetModel->index(musicLocation));
}
