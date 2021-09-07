#include "optionsdialog.h"
#include "ui_optionsdialog.h"
#include "GlobalSettings/globalsettings.h"

#include <QSettings>

OptionsDialog::OptionsDialog(bool isNew, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog),
    isNewConfig(isNew)
{
    ui->setupUi(this);

    createUI();
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::createUI()
{
    if(isNewConfig){

    } else {
        readOptions();
    }
}

void OptionsDialog::writeOptions()
{
    QSettings settings(GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);
    settings.beginGroup("DATABASE");
    settings.setValue("Server",ui->lineEditServer->text().trimmed());
    settings.setValue("Port",ui->lineEditPort->text().trimmed());
    settings.setValue("DataBase", ui->lineEditDataBase->text().trimmed());
    settings.setValue("User",ui->lineEditUser->text().trimmed());
    settings.setValue("Password", ui->lineEditPass->text().trimmed());
    settings.endGroup();

}

void OptionsDialog::readOptions()
{
    QSettings settings(GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);

    settings.beginGroup("DATABASE");
    ui->lineEditServer->setText(settings.value("Server").toString());
    ui->lineEditPort->setText(settings.value("Port").toString());
    ui->lineEditDataBase->setText(settings.value("Database").toString());
    ui->lineEditUser->setText(settings.value("User").toString());
    ui->lineEditPass->setText(settings.value("Password").toString());
    settings.endGroup();

}

void OptionsDialog::on_buttonBox_rejected()
{
    this->reject();
}

void OptionsDialog::on_buttonBox_accepted()
{
    writeOptions();
    this->accept();
}
