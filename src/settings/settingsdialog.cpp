#include "settingsdialog.h"

SettingsDialog::SettingsDialog()
{
    setWindowTitle("Settings");


    // TODO: add icons. Icons are friends!

    // Create buttons and a widget to enclose them
    QVBoxLayout *vbox = new QVBoxLayout();
    QWidget *buttonsWidget = new QWidget();
    QPushButton *addButon = new QPushButton("Add folder");
    QPushButton *removeButon = new QPushButton("Remove folder");
    vbox->addWidget(addButon);
    vbox->addWidget(removeButon);
    buttonsWidget->setLayout(vbox);

    // Horizontal box to put the folders list and buttons
    QHBoxLayout *hbox = new QHBoxLayout();
    QListWidget *folderList = new QListWidget();
    hbox->addWidget(folderList);
    hbox->addWidget(buttonsWidget);
    QWidget *central = new QWidget();
    central->setLayout(hbox);


    // Other vertical box to put the widgets created before.
    QVBoxLayout *mainVBox = new QVBoxLayout();
    mainVBox->addWidget(central);

    // TODO: put a separator here

    QWidget *mainWidget = new QWidget();
    mainWidget->setLayout(mainVBox);


    setCentralWidget(mainWidget);
    show();


}
