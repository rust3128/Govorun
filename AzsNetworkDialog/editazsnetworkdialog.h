#ifndef EDITAZSNETWORKDIALOG_H
#define EDITAZSNETWORKDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class EditAZSNetworkDialog;
}

class EditAZSNetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAZSNetworkDialog(QSqlRecord *curRec, QWidget *parent = nullptr);
    ~EditAZSNetworkDialog();

private slots:
    void on_toolButtonLoadLogo_clicked();

    void on_lineEditName_textChanged(const QString &name);

    void on_buttonBox_accepted();

private:
    void createUI();
private:
    Ui::EditAZSNetworkDialog *ui;
    QSqlRecord *editRecord;
    QByteArray inByteArray;
};

#endif // EDITAZSNETWORKDIALOG_H
