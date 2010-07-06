#ifndef LASTFMSETTINGSWIDGET_H
#define LASTFMSETTINGSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>
#include "../../lastfmsettings.h"

class LastFmSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    LastFmSettingsWidget(QWidget *parent);
    void applySettings();

private:
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLineEdit *usernameTextBox;
    QLineEdit *passwordTextBox;
    QCheckBox *active;

private slots:
    void handleLastFmState(bool enabled);

};

#endif // LASTFMSETTINGSWIDGET_H
