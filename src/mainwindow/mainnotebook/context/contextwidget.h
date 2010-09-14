#ifndef CONTEXTWIDGET_H
#define CONTEXTWIDGET_H

#include <QWidget>
#include <QPushButton>
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
    QMap<QString, QString> currentContext;

    QPushButton *artistButton;
    QPushButton *lyricsButton;


public slots:
    void songInformationUpdated(QMap<QString, QString> newContextInformation);
    void fetchButtonPressed();
};

#endif // CONTEXTWIDGET_H
