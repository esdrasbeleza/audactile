#include "mainwidget.h"

MainWidget::MainWidget()
{
    // Creates the horizontal layout where we'll put our notebook
    QHBoxLayout *layout = new QHBoxLayout();

    // Add the notebook
    layout->addWidget(new MainNotebook(this));

    // Create a test label.
    QLabel *label = new QLabel(tr("Test label"));
    layout->addWidget(label);

    setLayout(layout);
}
