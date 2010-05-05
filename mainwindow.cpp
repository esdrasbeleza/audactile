#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Creates the horizontal layout where we'll put our notebook
    QWidget* middleWidget = new QWidget();
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    MainNotebook *mainNotebook = new MainNotebook();
    QLabel *label2 = new QLabel(tr("Test label 2"));
    horizontalLayout->addWidget(mainNotebook, 1, Qt::AlignLeft);
    horizontalLayout->addWidget(label2, 1, Qt::AlignLeft);
    middleWidget->setLayout(horizontalLayout);

    // Create a vertical layout
    QWidget *mainVerticalWidget = new QWidget();
    QVBoxLayout *verticalLayout = new QVBoxLayout();

    middleWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //verticalLayout->addWidget(playerbar, 1, Qt::AlignLeft);
    verticalLayout->addWidget(middleWidget);
    mainVerticalWidget->setLayout(verticalLayout);
    setCentralWidget(mainVerticalWidget);

    PlayerBar *playerbar = new PlayerBar();
    addToolBar(playerbar);
}

MainWindow::~MainWindow()
{

}
