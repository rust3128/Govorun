#ifndef EDITFIRMSDIALOG_H
#define EDITFIRMSDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace Ui {
class EditFirmsDialog;
}

class EditFirmsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditFirmsDialog(QSqlQueryModel *modNet, QSqlRecord *record, QWidget *parent = nullptr);
    ~EditFirmsDialog();

private slots:
    void on_comboBoxNetworkAZS_activated(int idx);

    void on_lineEditName_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void createUI();
private:
    Ui::EditFirmsDialog *ui;
    QSqlRecord *curRecord;
    int currentNetworkID;
    QSqlQueryModel *modelNetwork;
};

#endif // EDITFIRMSDIALOG_H
