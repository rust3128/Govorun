#include "azsnetworkdialog.h"
#include "ui_azsnetworkdialog.h"
#include "AzsNetworkDialog/editazsnetworkdialog.h"



#include <QPushButton>

AzsNetworkDialog::AzsNetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AzsNetworkDialog)
{
    ui->setupUi(this);

    createModel();
    createUI();
}

AzsNetworkDialog::~AzsNetworkDialog()
{
    delete ui;
}

void AzsNetworkDialog::createUI()
{
    ui->tableView->setModel(modelNetwork);
    ui->tableView->setItemDelegateForColumn(2, logoDelegate);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(3);
    QHeaderView *headerView = ui->tableView->horizontalHeader();
    headerView->swapSections(2, 1);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

void AzsNetworkDialog::createModel()
{
    currentRecord = new QSqlRecord();
    logoDelegate = new LogoDelegate();
    modelNetwork = new AzsNetworkModel();
    modelNetwork->setTable("AZSNETWORK");
    modelNetwork->setHeaderData(2,Qt::Horizontal,"Лого");
    modelNetwork->setHeaderData(1,Qt::Horizontal,"Наименование");

    modelNetwork ->select();



}

void AzsNetworkDialog::on_pushButtonAdd_clicked()
{
    currentRecord->clear();
    EditAZSNetworkDialog *edAZSNetDlg = new EditAZSNetworkDialog(currentRecord,this);
    if(edAZSNetDlg->exec() == QDialog::Accepted){
        modelNetwork->select();
    }
}

void AzsNetworkDialog::on_pushButtonClose_clicked()
{
    this->reject();
}


void AzsNetworkDialog::on_tableView_doubleClicked(const QModelIndex &idx)
{
    QSqlRecord r = modelNetwork->record(idx.row());
    currentRecord = &r;
    EditAZSNetworkDialog *edAZSNetDlg = new EditAZSNetworkDialog(currentRecord,this);
    if(edAZSNetDlg->exec() == QDialog::Accepted){
        modelNetwork->select();
    }

}
