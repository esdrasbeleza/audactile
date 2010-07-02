#include "lastfmsettingswidget.h"

LastFmSettingsWidget::LastFmSettingsWidget(QWidget *parent) : QWidget(parent)
{
    usernameLabel = new QLabel("Username:", this);
    passwordLabel = new QLabel("Password:", this);
    usernameTextBox = new QLineEdit(this);
    passwordTextBox = new QLineEdit(this);
    passwordTextBox->setEchoMode(QLineEdit::Password);
    active = new QCheckBox("Active", this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(usernameLabel, 0, 0, Qt::AlignRight);
    layout->addWidget(usernameTextBox, 0, 1);
    layout->addWidget(passwordLabel, 1, 0, Qt::AlignRight);
    layout->addWidget(passwordTextBox, 1, 1);
    layout->addWidget(active, 2, 0, 1, 2);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    // TODO: make this fill better the window width.

    usernameTextBox->setText(LastFmSettings::username());
    passwordTextBox->setText(LastFmSettings::password());
    active->setChecked(LastFmSettings::isActive());
}

void LastFmSettingsWidget::applySettings() {
    LastFmSettings::setPassword(passwordTextBox->text());
    LastFmSettings::setUsername(usernameTextBox->text());
    LastFmSettings::setActive(active->isChecked());
}
