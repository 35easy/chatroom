#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_chatServer = new ChatServer(this);

    connect(m_chatServer,&ChatServer::logMessage,this,&MainWindow::logMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::logMessage(const QString &msg)
{
    ui->logEditor->appendPlainText(msg);
}


void MainWindow::on_btStartStop_clicked()
{

    if(m_chatServer->isListening()){
        m_chatServer->stopServer();
        ui->btStartStop->setText("启动服务器");
        logMessage("服务器已停止");
    }else{
        if(!m_chatServer->listen(QHostAddress::Any,1967)){
                QMessageBox::critical(this,"错误","无法启动服务器");
                return;
        }
        logMessage("服务器已经启动");
        ui->btStartStop->setText("停止服务器");

    }



//    static bool started=false;
//    started=!started;
//    if(started){
//        ui->btStartStop->setText("停止服务器");
//        logMessage("服务器已经启动");
//         }
//    else{
//        ui->btStartStop->setText("启动服务器");
//        logMessage("服务器已经停止");

//    }

}
