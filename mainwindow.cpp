#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Nameless player! :(");

    // Creates the horizontal layout where we'll put our notebook
    QSplitter* middleSplitter = new QSplitter();
    MainNotebook* mainNotebook = new MainNotebook();
    mainNotebook->setMinimumWidth(200);
    PlaylistWidget* playlistWidget = new PlaylistWidget();
    middleSplitter->addWidget(mainNotebook);
    middleSplitter->addWidget(playlistWidget);
    middleSplitter->setStretchFactor(0, 1);
    middleSplitter->setStretchFactor(1, 4);

    // Create a vertical layout
    QWidget *mainVerticalWidget = new QWidget();
    QVBoxLayout *verticalLayout = new QVBoxLayout();


    verticalLayout->addWidget(middleSplitter);
    mainVerticalWidget->setLayout(verticalLayout);
    setCentralWidget(mainVerticalWidget);

    // Includes our toolbar with more widgets, friendly called PlayerBar
    PlayerBar *playerbar = new PlayerBar();
    addToolBar(playerbar);
}

MainWindow::~MainWindow()
{

}
