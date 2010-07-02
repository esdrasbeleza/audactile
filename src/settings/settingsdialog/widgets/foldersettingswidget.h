#ifndef FOLDERSETTINGSWIDGET_H
#define FOLDERSETTINGSWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include "../../applicationsettings.h"

class FolderSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    FolderSettingsWidget(QWidget *parent);
    void applySettings();

private:
    QListWidget *folderList;
    QStringList originalFoldersList;

private slots:
    void addFolder();
    void removeFolder();

};

#endif // FOLDERSETTINGSWIDGET_H
