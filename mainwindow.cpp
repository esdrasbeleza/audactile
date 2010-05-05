#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Creates the horizontal layout where we'll put our notebook
    QWidget* middleWidget = new QWidget();
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    MainNotebook *mainNotebook = new MainNotebook();
    QLabel *label1 = new QLabel(tr("Test label 1"));
    horizontalLayout->addWidget(mainNotebook, 1, Qt::AlignLeft);
    horizontalLayout->addWidget(label1, 1, Qt::AlignLeft);
    middleWidget->setLayout(horizontalLayout);

    // Create a vertical layout
    QWidget *mainVerticalWidget = new QWidget();
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QLabel *label2 = new QLabel(tr("Test label 2"));
    middleWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    verticalLayout->addWidget(label2);
    verticalLayout->addWidget(middleWidget);

    mainVerticalWidget->setLayout(verticalLayout);
    setCentralWidget(mainVerticalWidget);
}

MainWindow::~MainWindow()
{

}
