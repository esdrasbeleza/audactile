#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Creates the horizontal layout where we'll put our notebook
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout();

    MainNotebook *mainNotebook = new MainNotebook();
    layout->addWidget(mainNotebook);

    // Create a test label.
    QLabel *label1 = new QLabel(tr("Test label 1"));
    QLabel *label2 = new QLabel(tr("Test label 2"));
    layout->addWidget(label1);
    layout->addWidget(label2);

    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{

}
