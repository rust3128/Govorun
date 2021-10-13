#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OptionsDialog/optionsdialog.h"
#include "AzsNetworkDialog/azsnetworkdialog.h"
#include "Firms/firmsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_menuOptions_triggered()
{
    OptionsDialog *optDlg = new OptionsDialog(false);
    optDlg->exec();
}

void MainWindow::on_menuAzsNetwork_triggered()
{
    AzsNetworkDialog *azsNetDlg = new AzsNetworkDialog();
    azsNetDlg->exec();
}

void MainWindow::on_menuFirms_triggered()
{
    FirmsDialog *firmsDlg = new FirmsDialog();
    firmsDlg->exec();
}
