#ifndef AZSNETWORKDIALOG_H
#define AZSNETWORKDIALOG_H

#include <QDialog>

namespace Ui {
class AzsNetworkDialog;
}

class AzsNetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AzsNetworkDialog(QWidget *parent = nullptr);
    ~AzsNetworkDialog();

private:
    void createUI();
private:
    Ui::AzsNetworkDialog *ui;
};

#endif // AZSNETWORKDIALOG_H
