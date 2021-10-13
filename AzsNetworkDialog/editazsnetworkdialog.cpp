#include "editazsnetworkdialog.h"
#include "ui_editazsnetworkdialog.h"
#include "LoggingCategories/loggingcategories.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextCodec>

EditAZSNetworkDialog::EditAZSNetworkDialog(QSqlRecord *curRec, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAZSNetworkDialog),
    editRecord(curRec)
{
    ui->setupUi(this);
    createUI();
}

EditAZSNetworkDialog::~EditAZSNetworkDialog()
{
    delete ui;
}

void EditAZSNetworkDialog::on_toolButtonLoadLogo_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть логотип"), "", tr("Изображения (*.png *.jpeg *.jpg);;Все файлы (*.*)"));
    QPixmap inPixmap(fileName); // Сохраняем его в изображение объекта QPixmap;

    if(inPixmap.width()>800 || inPixmap.height()>600){
        QMessageBox::warning(this,"Внимание","Размер логотипа слишком большой. Выберите другой файл.");
        return;
    }

    ui->labelLogo->setPixmap(inPixmap);
    QBuffer inBuffer( &inByteArray );                   // Сохранение изображения производим через буффер
    inBuffer.open( QIODevice::WriteOnly );              // Открываем буффер
    inPixmap.save( &inBuffer, "PNG" );                  // Записываем inPixmap в inByteArray

}

void EditAZSNetworkDialog::createUI()
{
    if(editRecord->isEmpty()){
        this->setWindowTitle("Новая сеть АЗС");
        ui->checkBoxIsActive->setChecked(true);
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
        inByteArray.clear();
    } else {
        this->setWindowTitle("Редактирование данных по сети АЗС");
        ui->lineEditName->setText(editRecord->value(1).toString());
        ui->checkBoxIsActive->setChecked(editRecord->value(3).toBool());
        QPixmap outPixmap = QPixmap();
        inByteArray = editRecord->value(2).toByteArray();
        outPixmap.loadFromData(inByteArray);
        if(!outPixmap.isNull())
            ui->labelLogo->setPixmap(outPixmap);
        else
            ui->labelLogo->setText("Логотип отсутствует");

    }
}

void EditAZSNetworkDialog::on_lineEditName_textChanged(const QString &name)
{
    bool enabled = (name.length() >2) ? true : false;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(enabled);
}

void EditAZSNetworkDialog::on_buttonBox_accepted()
{
    if(editRecord->isEmpty()){
        int result = QMessageBox::question(this,tr("Вопрос"),
                                           QString(tr("Вы дейстиветльно хотите добавить клиента %1 в базу данных?"))
                                           .arg(ui->lineEditName->text().trimmed()));
        if(result == QMessageBox::Yes){
            QSqlQuery q;
            q.prepare("INSERT INTO azsnetwork (name, logo, isactive) "
                      "VALUES (:name, :logo, :isactive )");
            q.bindValue(":name", ui->lineEditName->text().trimmed());
            q.bindValue(":logo", inByteArray);
            q.bindValue(":isactive", QVariant(ui->checkBoxIsActive->isChecked()).toInt());

            if(!q.exec()) {
                qCritical(logCritical()) << "Не возможно добавить клиента." << Qt::endl << q.lastError().text();
                return;
            }
            qInfo(logInfo()) << "Клиент добавлен.";
        }
    } else {
        int result = QMessageBox::question(this,tr("Вопрос"),
                                           QString(tr("Вы дейстиветльно хотите обновить информацию о клиенте %1 в базе данных?"))
                                           .arg(ui->lineEditName->text().trimmed()));
        if(result == QMessageBox::Yes){
            QSqlQuery q;
            q.prepare("UPDATE azsnetwork SET name = :name, logo = :logo, isactive = :isactive "
                      "WHERE NETWORK_ID = :networkID");
            q.bindValue(":name", ui->lineEditName->text().trimmed());
            q.bindValue(":logo",  inByteArray);
            q.bindValue(":isactive", QVariant(ui->checkBoxIsActive->isChecked()).toInt());
            q.bindValue(":networkID", editRecord->value(0).toInt());
            if(!q.exec()) {
                qCritical(logCritical()) << "Не возможно обновить данные клиента." << endl << q.lastError().text();
                return;
            }
            qInfo(logInfo()) << "Информация о клиенте обновлена.";

        }
    }

    this->accept();
}

void EditAZSNetworkDialog::on_buttonBox_rejected()
{
    this->reject();
}

