#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Settings");
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);

    // TODO: add icons. Icons are friends!

    // List to show the selected configuration
    QListWidget *listWidget = new QListWidget(this);
    listWidget->setViewMode(QListView::IconMode);
    listWidget->setIconSize(QSize(48, 48));
    QLabel *label = new QLabel(this);
    listWidget->setMaximumHeight(96 + 2*label->minimumHeight());
    listWidget->setSpacing(12);
    listWidget->setMovement(QListView::Static);


    // Create tab bar
    QStackedWidget *settingsStack = new QStackedWidget(this);

    // Settings widgets
    QListWidgetItem *folderSettingsListItem = new QListWidgetItem(IconFactory::fromTheme("system-file-manager"), "Collection folders");
    folderSettingsWidget = new FolderSettingsWidget(this);
    QListWidgetItem *lastFmSettingsListItem = new QListWidgetItem(QIcon(":icons/lastfm.png"), "Last.fm");
    lastFmSettingsWidget = new LastFmSettingsWidget(this);

    /*
     * Add the widgets above to stacked widget and
     * make a reference for them in the list
     */
    listWidget->addItem(folderSettingsListItem);
    settingsStack->addWidget(folderSettingsWidget);
    listWidget->addItem(lastFmSettingsListItem);
    settingsStack->addWidget(lastFmSettingsWidget);

    // Link listwidget and settings stack
    connect(listWidget, SIGNAL(currentRowChanged(int)), settingsStack, SLOT(setCurrentIndex(int)));

    // Create button box
    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply);

    // Other vertical box to put the widgets created before.
    QVBoxLayout *mainVBox = new QVBoxLayout();
    mainVBox->addWidget(listWidget, 0);
    mainVBox->addWidget(Separator::horizontalSeparator(this));
    mainVBox->addWidget(settingsStack);
    mainVBox->addWidget(Separator::horizontalSeparator(this));
    mainVBox->addWidget(buttonBox);
    setLayout(mainVBox);

    // Connect buttons to their slots
    connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(handleAbstractButton(QAbstractButton*)));

    // Show window!
    show();

    // Center window
    int x = (parent->width() - width())/2;
    int y = (parent->height() - height())/2;
    move(x, y);

    // Set this to remove maximize buttons!
    setFixedSize(width(), height());
}



void SettingsDialog::applySettings() {
    folderSettingsWidget->applySettings();
    lastFmSettingsWidget->applySettings();
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
