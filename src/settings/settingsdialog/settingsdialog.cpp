#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Settings");
    setWindowFlags(Qt::Dialog);
    setWindowModality(Qt::ApplicationModal);

    // TODO: add icons. Icons are friends!

    // Create tab bar
    QTabWidget *settingsTab = new QTabWidget(this);

    folderSettingsWidget = new FolderSettingsWidget(this);
    lastFmSettingsWidget = new LastFmSettingsWidget(this);

    settingsTab->addTab(folderSettingsWidget, "Collection folders");
    settingsTab->addTab(lastFmSettingsWidget, "Last.fm");

    // Create button box
    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Apply);

    // Other vertical box to put the widgets created before.
    QVBoxLayout *mainVBox = new QVBoxLayout();
    mainVBox->addWidget(settingsTab);
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
