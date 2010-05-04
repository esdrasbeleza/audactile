#include "mainnotebook.h"

MainNotebook::MainNotebook()
{
    setTabPosition(QTabWidget::West);


    // Creates a label test widget
    QLabel *testLabel1 = new QLabel(tr("Test label 1"));
    QLabel *testLabel2 = new QLabel(tr("Test label 2"));
    QLabel *testLabel3 = new QLabel(tr("Test label 3"));

    // Creates a tree widget
    QTreeWidget *collectionWidget = new QTreeWidget();
    collectionWidget->setColumnCount(1);
    QList<QTreeWidgetItem *> items;

    QTreeWidgetItem *item1 = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Artista 1"));
    QTreeWidgetItem *item2 = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Artista 2"));
    QTreeWidgetItem *item3 = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Artista 3"));
    QTreeWidgetItem *item4 = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Artista 4"));
    items.append(item1);
    items.append(item2);
    items.append(item3);
    items.append(item4);

    /*
     * TODO:
     *  - Criar uma classe com a collection Widget
     *  - Métodos para adicionar/remover artista, música, etc.
     *
     */

    collectionWidget->insertTopLevelItems(0, items);


    // Creates one tab.
    addTab(collectionWidget, tr("Collection"));
    addTab(testLabel2, tr("Context"));
    addTab(testLabel3, tr("Playlists"));


    show();
}
