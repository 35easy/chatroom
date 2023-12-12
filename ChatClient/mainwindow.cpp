#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_btLogin_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
}

void MainWindow::on_btSay_clicked()
{

}

void MainWindow::on_btLogout_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->loginPage);

}
