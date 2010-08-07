#ifndef CONTEXTWIDGET_H
#define CONTEXTWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include "artistinfowidget.h"
#include "lyricswidget.h"

class ContextWidget : public QWidget
{
    Q_OBJECT

public:
    ContextWidget(QWidget *parent);

private:
    QButtonGroup *buttonGroup;
    ArtistInfoWidget *artistInfoWidget;
    LyricsWidget *lyricsWidget;


public slots:
    void songInformationUpdated(QMap<QString, QString> newContextInformation);
};

#endif // CONTEXTWIDGET_H
