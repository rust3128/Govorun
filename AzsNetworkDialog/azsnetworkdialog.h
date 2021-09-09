#ifndef AZSNETWORKDIALOG_H
#define AZSNETWORKDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class AzsNetworkDialog;
}

class AzsNetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AzsNetworkDialog(QWidget *parent = nullptr);
    ~AzsNetworkDialog();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonClose_clicked();

private:
    void createUI();
    void createModel();
private:
    Ui::AzsNetworkDialog *ui;
    QSqlRecord *currentRecord;
};

#endif // AZSNETWORKDIALOG_H
