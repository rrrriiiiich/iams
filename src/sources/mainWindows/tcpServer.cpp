#include "tcpServer.h"
#include "ui_tcpServer.h"

tcpServer::tcpServer(QWidget *parent) : QMainWindow(parent),
                                        ui(new Ui::tcpServer)
{
    ui->setupUi(this);

    qtcpServer = new QTcpServer(this);
    qtcpSocket = new QTcpSocket(this);

    // 默认设置发送内容
    ui->sendPlainTextEdit->setPlainText("你好 客户端");
}

tcpServer::~tcpServer()
{
    delete ui;
}

void tcpServer::on_listenButton_clicked()
{
    qtcpServer->listen(QHostAddress::Any, ui->portEdit->text().toInt());

    qDebug() << "tcp server addresses:";
    for (const tcpServerAddress &address : getAvailableNetworkAddresses())
    {
        qDebug() << address.name << ":" << address.address.toString();
    }

    if (qtcpServer->isListening())
    {
        qDebug() << "listen success";
    }
    else
    {
        qDebug() << "listen fail";
    }

    connect(qtcpServer, &QTcpServer::newConnection, this, &tcpServer::on_newConnection);
}

void tcpServer::on_newConnection()
{
    qDebug() << "new connection";

    qtcpSocket = qtcpServer->nextPendingConnection();

    connect(qtcpSocket, &QTcpSocket::readyRead, this, &tcpServer::readData);
}

void tcpServer::readData()
{
    qDebug() << "read data";
    ui->recvTextEdit->appendPlainText(qtcpSocket->readAll());
}

void tcpServer::on_sendButton_clicked()
{
    qDebug() << "send button clicked";
    qtcpSocket->write(ui->sendPlainTextEdit->toPlainText().toUtf8());
}

void tcpServer::on_backButton_clicked()
{
    this->parentWidget()->show();
    this->close();
}
