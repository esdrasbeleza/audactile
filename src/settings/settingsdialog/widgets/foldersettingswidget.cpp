#include "foldersettingswidget.h"

FolderSettingsWidget::FolderSettingsWidget(QWidget *parent) : QWidget(parent)
{
    // Create buttons and a widget to enclose them
    QVBoxLayout *vbox = new QVBoxLayout();
    QWidget *buttonsWidget = new QWidget();
    QPushButton *addButton = new QPushButton("Add folder");
    QPushButton *removeButton = new QPushButton("Remove folder");
    vbox->addWidget(addButton);
    vbox->addWidget(removeButton);
    buttonsWidget->setLayout(vbox);

    // Horizontal box to put the folders list and buttons
    QHBoxLayout *hbox = new QHBoxLayout();
    folderList = new QListWidget();
    folderList->setSelectionMode(QListWidget::ExtendedSelection);
    hbox->addWidget(folderList);
    hbox->addWidget(buttonsWidget);
    setLayout(hbox);

    // Update data
    ApplicationSettings *settings = new ApplicationSettings();
    originalFoldersList = settings->collectionFolderList();
    foreach (QString folder, originalFoldersList) {
        folderList->addItem(folder);
    }
    delete settings;
    

    connect(addButton, SIGNAL(clicked()), this, SLOT(addFolder()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeFolder()));
}

void FolderSettingsWidget::addFolder() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Add folder"), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QDir qdir;
    if (!dir.isEmpty() && qdir.exists(dir)) {
        folderList->addItem(dir);
        folderList->sortItems();
    }
}

void FolderSettingsWidget::removeFolder() {
    if (folderList->selectedItems().count() == 0) return;
    foreach(QListWidgetItem *item, folderList->selectedItems()) {
        delete item;
    }
}

void FolderSettingsWidget::applySettings() {
    ApplicationSettings *settings = new ApplicationSettings();

    /*
     *
     * Settings for folders
     *
     */
    QStringList folders;
    for(int i = 0; i < folderList->count(); i++) {
        QListWidgetItem *item = folderList->item(i);
        folders.append(item->text());
    }
    settings->setCollectionFolders(folders);

    // If folders have changed, rebuild the collection database
    if (folders != originalFoldersList) {
        // TODO: rebuild collection
        originalFoldersList = folders;
    }


    /*
     *
     * Settings for folders - end
     *
     */

    delete settings;
}
