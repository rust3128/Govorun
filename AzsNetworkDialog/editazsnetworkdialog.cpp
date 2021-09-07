#include "editazsnetworkdialog.h"
#include "ui_editazsnetworkdialog.h"

EditAZSNetworkDialog::EditAZSNetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAZSNetworkDialog)
{
    ui->setupUi(this);
}

EditAZSNetworkDialog::~EditAZSNetworkDialog()
{
    delete ui;
}
