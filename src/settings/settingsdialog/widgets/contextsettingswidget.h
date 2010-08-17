#ifndef CONTEXTSETTINGSWIDGET_H
#define CONTEXTSETTINGSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>
#include "../../contextsettings.h"

class ContextSettingsWidget : public QWidget
{
public:
    explicit ContextSettingsWidget(QWidget *parent = 0);
    void applySettings();

private:
    QCheckBox *fetchSummary;
    QCheckBox *fetchLyrics;

};

#endif // CONTEXTSETTINGSWIDGET_H
