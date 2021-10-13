#ifndef FIRMSDIALOG_H
#define FIRMSDIALOG_H

#include "Firms/mymodelfirms.h"

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QItemSelection>

namespace Ui {
class FirmsDialog;
}

class FirmsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FirmsDialog(QWidget *parent = nullptr);
    ~FirmsDialog();
signals:
    void signalChangeFilter();
private slots:
    void slotFirmSelected(const QItemSelection &, const QItemSelection &);
    void slotChangeFilter();
    void on_toolButtonExit_clicked();
    void on_comboBoxNetwork_activated(int idx);
    void on_toolButtonAdd_clicked();
    void on_toolButtonEdit_clicked();

    void on_checkBoxIsActive_clicked();

private:
    void createUI();
    void createModels();
    void createConnections();
private:
    Ui::FirmsDialog *ui;
    QSqlQueryModel *modelNetwork;
    int currentNetworkID;
    QString strFilter;
    MyModelFirms *modelFirms;
    QSqlRecord *currRecord;
    QSqlRecord rec;

};

#endif // FIRMSDIALOG_H
