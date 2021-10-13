#ifndef AZSNETWORKDIALOG_H
#define AZSNETWORKDIALOG_H

#include "AzsNetworkDialog/azsnetworkmodel.h"
#include "AzsNetworkDialog/logodelegate.h"

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

    void on_tableView_doubleClicked(const QModelIndex &idx);

private:
    void createUI();
    void createModel();
private:
    Ui::AzsNetworkDialog *ui;
    QSqlRecord *currentRecord;
    AzsNetworkModel *modelNetwork;
    LogoDelegate *logoDelegate;
};

#endif // AZSNETWORKDIALOG_H
