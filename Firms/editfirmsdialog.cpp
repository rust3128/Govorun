#include "editfirmsdialog.h"
#include "ui_editfirmsdialog.h"
#include "LoggingCategories/loggingcategories.h"

#include <QPushButton>

EditFirmsDialog::EditFirmsDialog(QSqlQueryModel *modNet, QSqlRecord *record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditFirmsDialog),
    curRecord(record),
    modelNetwork(modNet)
{
    ui->setupUi(this);

    createUI();
}

EditFirmsDialog::~EditFirmsDialog()
{
    delete ui;
}

void EditFirmsDialog::createUI()
{

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
    ui->comboBoxNetworkAZS->setModel(modelNetwork);
    ui->comboBoxNetworkAZS->setModelColumn(1);


    if(curRecord->isEmpty()){
        this->setWindowTitle("Новая фирма");
        ui->comboBoxNetworkAZS->setCurrentIndex(-1);
        ui->comboBoxNetworkAZS->setCurrentText("Выберите сеть АЗС");
    } else {

        int idxComBox;
        for(idxComBox=0;idxComBox<modelNetwork->rowCount();++idxComBox) {
            if(modelNetwork->data(modelNetwork->index(idxComBox,0)).toInt()==curRecord->value(1).toInt()){
                break;
            }
        }
        this->setWindowTitle("Редактирование фирмы");
        qInfo(logInfo()) << "Current comboBox" << idxComBox;
        ui->comboBoxNetworkAZS->setCurrentIndex(idxComBox);
        currentNetworkID=curRecord->value(1).toInt();
        ui->lineEditName->setText(curRecord->value(2).toString());
        ui->lineEditOKPO->setText(curRecord->value(3).toString());
        ui->checkBoxIsActive->setChecked(curRecord->value(4).toBool());
    }

}

void EditFirmsDialog::on_comboBoxNetworkAZS_activated(int idx)
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(ui->lineEditName->text().size()>3 && ui->comboBoxNetworkAZS->currentIndex()>=0);
    currentNetworkID = modelNetwork->data(modelNetwork->index(idx,0)).toInt();
}

void EditFirmsDialog::on_lineEditName_textChanged(const QString &arg1)
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(arg1.size()>3 && ui->comboBoxNetworkAZS->currentIndex()>=0);
}

void EditFirmsDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    if(curRecord->isEmpty()){
        q.prepare("INSERT INTO FIRMS (NETWORK_ID, NAME, OKPO, ISACTIVE) VALUES (:networkID, :name, :okpo, :isactive)");
        q.bindValue(":networkID",currentNetworkID);
        q.bindValue(":name", ui->lineEditName->text().trimmed());
        q.bindValue(":okpo", ui->lineEditOKPO->text().trimmed());
        q.bindValue(":isactive", QVariant(ui->checkBoxIsActive->isChecked()).toInt());

        if(!q.exec()) {
            qCritical(logCritical()) << "Не возможно добавить клиента." << Qt::endl << q.lastError().text();
            return;
        }
        qInfo(logInfo()) << "Клиент добавлен.";
    } else {
        q.prepare("UPDATE FIRMS SET NETWORK_ID = :networkID, NAME = :name, OKPO = :okpo, ISACTIVE = :isactive  WHERE (FIRM_ID = :firmID)");
        q.bindValue(":networkID",currentNetworkID);
        q.bindValue(":name", ui->lineEditName->text().trimmed());
        q.bindValue(":okpo", ui->lineEditOKPO->text().trimmed());
        q.bindValue(":isactive", QVariant(ui->checkBoxIsActive->isChecked()).toInt());
        q.bindValue(":firmID",curRecord->value(0).toInt());
        if(!q.exec()) {
            qCritical(logCritical()) << "Не возможно обновить данные о клиенте." << Qt::endl << q.lastError().text();
            return;
        }
        qInfo(logInfo()) << "Данные о клиенте обновлены.";

    }
    this->accept();
}

void EditFirmsDialog::on_buttonBox_rejected()
{
    this->reject();
}
