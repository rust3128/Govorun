#ifndef EDITAZSNETWORKDIALOG_H
#define EDITAZSNETWORKDIALOG_H

#include <QDialog>

namespace Ui {
class EditAZSNetworkDialog;
}

class EditAZSNetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAZSNetworkDialog(QWidget *parent = nullptr);
    ~EditAZSNetworkDialog();

private:
    Ui::EditAZSNetworkDialog *ui;
};

#endif // EDITAZSNETWORKDIALOG_H
