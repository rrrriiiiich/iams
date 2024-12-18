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
        qDebug() << "listen success";
    }
    else
    {
        qDebug() << "listen fail";
    }

    connect(tcpServer, &QTcpServer::newConnection, this, &tcpServerWindow::on_newConnection);
}

void tcpServerWindow::on_newConnection()
{
    qDebug() << "new connection";

    tcpSocket = tcpServer->nextPendingConnection();

    connect(tcpSocket, &QTcpSocket::readyRead, this, &tcpServerWindow::readData);
}

void tcpServerWindow::readData()
{
    qDebug() << "read data";
    ui->recvTextEdit->appendPlainText(tcpSocket->readAll());
}

void tcpServerWindow::on_sendButton_clicked()
{
    qDebug() << "send button clicked";
    tcpSocket->write(ui->sendPlainTextEdit->toPlainText().toUtf8());
}

void tcpServerWindow::on_backButton_clicked()
{
    this->parentWidget()->show();
    this->close();
}
