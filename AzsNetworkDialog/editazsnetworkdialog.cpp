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
    }

    this->accept();
}

void EditAZSNetworkDialog::on_buttonBox_rejected()
{
    this->reject();
}

