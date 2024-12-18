#include "tcpserverwindow.h"
#include "ui_tcpserverwindow.h"

tcpServerWindow::tcpServerWindow(QWidget *parent) : QMainWindow(parent),
                                                    ui(new Ui::tcpServerWindow)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);

    // 默认设置发送内容
    ui->sendPlainTextEdit->setPlainText("你好 客户端");
}

tcpServerWindow::~tcpServerWindow()
{
    delete ui;
}

void tcpServerWindow::on_listenButton_clicked()
{
    tcpServer->listen(QHostAddress::Any, ui->portEdit->text().toInt());

    if (tcpServer->isListening())
    {
        qDebug() << "监听成功";
    }
    else
    {
        qDebug() << "监听失败";
    }

    connect(tcpServer, &QTcpServer::newConnection, this, &tcpServerWindow::on_newConnection);
}

void tcpServerWindow::on_newConnection()
{
    qDebug() << "新连接";

    tcpSocket = tcpServer->nextPendingConnection();

    connect(tcpSocket, &QTcpSocket::readyRead, this, &tcpServerWindow::readData);
}

void tcpServerWindow::readData()
{
    qDebug() << "接收到数据";
    ui->recvTextEdit->appendPlainText(tcpSocket->readAll());
}

void tcpServerWindow::on_sendButton_clicked()
{
    qDebug() << "发送数据";
    tcpSocket->write(ui->sendPlainTextEdit->toPlainText().toUtf8());
}
