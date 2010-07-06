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
    layout->addWidget(active, 0, 0, 1, 2);
    layout->addWidget(usernameLabel, 1, 0, Qt::AlignRight);
    layout->addWidget(usernameTextBox, 1, 1);
    layout->addWidget(passwordLabel, 2, 0, Qt::AlignRight);
    layout->addWidget(passwordTextBox, 2, 1);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    // TODO: make this fill better the window width.

    usernameTextBox->setText(LastFmSettings::username());
    passwordTextBox->setText(LastFmSettings::password());
    active->setChecked(LastFmSettings::isActive());

    // If Last.fm is not active, disable the textboxes
    if (!active->isChecked()) {
        usernameTextBox->setDisabled(true);
        passwordTextBox->setDisabled(true);
        usernameLabel->setDisabled(true);
        passwordLabel->setDisabled(true);
    }
    connect(active, SIGNAL(toggled(bool)), this, SLOT(handleLastFmState(bool)));


}

void LastFmSettingsWidget::applySettings() {
    LastFmSettings::setPassword(passwordTextBox->text());
    LastFmSettings::setUsername(usernameTextBox->text());
    LastFmSettings::setActive(active->isChecked());
}

void LastFmSettingsWidget::handleLastFmState(bool enabled) {
    usernameLabel->setEnabled(enabled);
    usernameTextBox->setEnabled(enabled);
    passwordLabel->setEnabled(enabled);
    passwordTextBox->setEnabled(enabled);
}
