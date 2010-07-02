#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QSpacerItem>
#include <QApplication>
#include <QDesktopWidget>
#include <QDialogButtonBox>
#include <QFileDialog>
#include "applicationsettings.h"

class SettingsDialog : public QWidget
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent);

private:
    void updateMediaFolders();
    QListWidget *folderList;
    QDialogButtonBox *buttonBox;
    QStringList originalFoldersList;

private slots:
    void addFolder();
    void removeFolder();
    void applySettings();
    void handleAbstractButton(QAbstractButton*);


};

#endif // SETTINGSDIALOG_H
