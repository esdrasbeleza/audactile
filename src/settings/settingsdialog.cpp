#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Settings");
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);

    // TODO: add icons. Icons are friends!

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
    QWidget *central = new QWidget();
    central->setLayout(hbox);

    // Create button box
    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply);

    // Other vertical box to put the widgets created before.
    QVBoxLayout *mainVBox = new QVBoxLayout();
    mainVBox->addWidget(central);
    mainVBox->addWidget(buttonBox);
    setLayout(mainVBox);

    // Connect buttons to their slots
    connect(addButton, SIGNAL(clicked()), this, SLOT(addFolder()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeFolder()));
    connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(handleAbstractButton(QAbstractButton*)));

    // Show window!
    show();

    // Center window
    int x = (QApplication::desktop()->width() - width())/2;
    int y = (QApplication::desktop()->height() - height())/2;
    move(x, y);

    // Set this to remove maximize buttons!
    setFixedSize(width(), height());

    // Update data
    ApplicationSettings *settings = new ApplicationSettings();
    originalFoldersList = settings->collectionFolderList();
    foreach (QString folder, originalFoldersList) {
        folderList->addItem(folder);
    }
    delete settings;
}

void SettingsDialog::addFolder() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Add folder"), QDir::homePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QDir qdir;
    if (!dir.isEmpty() && qdir.exists(dir)) {
        folderList->addItem(dir);
        folderList->sortItems();
    }
}

void SettingsDialog::removeFolder() {
    if (folderList->selectedItems().count() == 0) return;
    foreach(QListWidgetItem *item, folderList->selectedItems()) {
        delete item;
    }
}

void SettingsDialog::applySettings() {
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

void SettingsDialog::handleAbstractButton(QAbstractButton *button) {
    qDebug("handleAbstractButton()");
    switch (buttonBox->buttonRole(button)) {
    case QDialogButtonBox::ApplyRole:
        applySettings();
        break;
    case QDialogButtonBox::AcceptRole:
        applySettings();
        close();
        break;
    case QDialogButtonBox::RejectRole:
        close();
        break;
    default:
        // Does nothing
        break;
    }
}
