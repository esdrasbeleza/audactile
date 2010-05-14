#include "filesystemwidget.h"

FilesystemWidget::FilesystemWidget()
{
    startLocation = QDesktopServices::storageLocation(QDesktopServices::MusicLocation);
    if (startLocation.isEmpty() || !dir.exists(startLocation)) {
        dir = QDir(QDir::homePath());
    }
    else {
        dir = QDir(startLocation);
    }

    // Create the toolbar
    QToolBar* fsToolbar = new QToolBar();
    fsToolbar->setMovable(false);
    QToolButton* homeButton = new QToolButton();
    homeButton->setIcon(QIcon::fromTheme("go-home"));

    goUpAction = new QAction(QIcon::fromTheme("go-up"), tr("Go up"), this);
    connect(goUpAction, SIGNAL(triggered()), this, SLOT(goUp()));
    fsToolbar->addAction(goUpAction);


    // Create the filesystem view
    fsWidgetModel = new QFileSystemModel();

    fsWidgetModel->setRootPath(dir.absolutePath());
    fsListView = new QListView();
    fsListView->setModel(fsWidgetModel);
    fsListView->setRootIndex(fsWidgetModel->index(dir.absolutePath()));

    // Create a new horizontal box
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(fsToolbar);
    vlayout->addWidget(fsListView);

    this->setLayout(vlayout);

}


void FilesystemWidget::goUp() {
    dir.cdUp();
    fsWidgetModel->setRootPath(dir.absolutePath());
    fsListView->setRootIndex(fsWidgetModel->index(dir.absolutePath()));

    // Disable go up button
    if (dir.absolutePath() == QDir::rootPath()) { goUpAction->setDisabled(true); }
    else { goUpAction->setDisabled(false); }
}

