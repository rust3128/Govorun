#include "firmsdialog.h"
#include "ui_firmsdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include "Firms/editfirmsdialog.h"

FirmsDialog::FirmsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirmsDialog)
{
    ui->setupUi(this);

    createModels();
    createUI();
    createConnections();
}

FirmsDialog::~FirmsDialog()
{
    delete ui;
}

void FirmsDialog::slotFirmSelected(const QItemSelection &, const QItemSelection &)
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedIndexes();
    rec = modelFirms->record(selection.at(0).row());
    ui->toolButtonEdit->setEnabled(true);
}

void FirmsDialog::slotChangeFilter()
{
    strFilter = "NETWORK_ID = "+QString::number(currentNetworkID);
    if(ui->checkBoxIsActive->isChecked()){
        strFilter += " and ISACTIVE = 1";
    }
}

void FirmsDialog::on_toolButtonExit_clicked()
{
    this->reject();
}

void FirmsDialog::createUI()
{
    ui->checkBoxIsActive->setChecked(true);
    currRecord = new QSqlRecord;
    ui->toolButtonEdit->setEnabled(false);
    ui->comboBoxNetwork->setModel(modelNetwork);
    ui->comboBoxNetwork->setModelColumn(1);
    ui->comboBoxNetwork->setCurrentIndex(-1);
    ui->comboBoxNetwork->setCurrentText("Выберите сеть АЗС");
    currentNetworkID = -1;
    ui->tableView->setModel(modelFirms);

    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void FirmsDialog::createModels()
{
    modelNetwork = new QSqlQueryModel();
    modelNetwork->setQuery("SELECT n.network_id, n.name FROM azsnetwork n WHERE n.isactive = 1 ORDER BY n.network_id");
    if(modelNetwork->lastError().isValid()){
        qCritical(logCritical()) << "Ошибка создания модели фирм" << modelNetwork->lastError().text();
        this->reject();
    }
    modelFirms = new MyModelFirms();
    modelFirms->setTable("FIRMS");

    modelFirms->setHeaderData(2,Qt::Horizontal,"Наименование");
    modelFirms->setHeaderData(3,Qt::Horizontal,"ОКПО");
    modelFirms->setHeaderData(4,Qt::Horizontal,"Активна");

}

void FirmsDialog::createConnections()
{
    connect(ui->tableView->selectionModel(),&QItemSelectionModel::selectionChanged,this,&FirmsDialog::slotFirmSelected);
    connect(this,&FirmsDialog::signalChangeFilter,this,&FirmsDialog::slotChangeFilter);
}

void FirmsDialog::on_comboBoxNetwork_activated(int idx)
{
    currentNetworkID = modelNetwork->data(modelNetwork->index(idx,0)).toInt();
    emit signalChangeFilter();
    modelFirms->select();
    modelFirms->setFilter(strFilter);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void FirmsDialog::on_toolButtonAdd_clicked()
{
    currRecord->clear();
    EditFirmsDialog *editFirmsDlg = new EditFirmsDialog(modelNetwork,currRecord);
    if(editFirmsDlg->exec() == QDialog::Accepted){
        modelFirms->select();
        ui->tableView->resizeColumnsToContents();
    }
}

void FirmsDialog::on_toolButtonEdit_clicked()
{
    currRecord = &rec;
    EditFirmsDialog *editFirmsDlg = new EditFirmsDialog(modelNetwork,currRecord);
    if(editFirmsDlg->exec() == QDialog::Accepted){
        modelFirms->select();
        ui->tableView->resizeColumnsToContents();
    }
    modelFirms->select();
    modelFirms->setFilter(strFilter);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void FirmsDialog::on_checkBoxIsActive_clicked()
{
    emit signalChangeFilter();
    modelFirms->select();
    modelFirms->setFilter(strFilter);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}
