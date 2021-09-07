#include "azsnetworkdialog.h"
#include "ui_azsnetworkdialog.h"

#include <QPushButton>

AzsNetworkDialog::AzsNetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AzsNetworkDialog)
{
    ui->setupUi(this);
    createUI();
}

AzsNetworkDialog::~AzsNetworkDialog()
{
    delete ui;
}

void AzsNetworkDialog::createUI()
{

}
