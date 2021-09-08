#include "azsnetworkdialog.h"
#include "ui_azsnetworkdialog.h"
#include "AzsNetworkDialog/editazsnetworkdialog.h"

#include <QPushButton>

AzsNetworkDialog::AzsNetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AzsNetworkDialog)
{
    ui->setupUi(this);
    createUI();
    createModel();
}

AzsNetworkDialog::~AzsNetworkDialog()
{
    delete ui;
}

void AzsNetworkDialog::createUI()
{

}

void AzsNetworkDialog::createModel()
{
    currentRecord = new QSqlRecord();
}

void AzsNetworkDialog::on_pushButtonAdd_clicked()
{
    currentRecord->clear();
    EditAZSNetworkDialog *edAZSNetDlg = new EditAZSNetworkDialog(currentRecord);
    edAZSNetDlg->exec();
}
