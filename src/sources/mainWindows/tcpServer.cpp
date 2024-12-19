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

    // 添加空选项到下拉框
    ui->addressComboBox->addItem("所有地址: 0.0.0.0");

    // 将getAvailableNetworkAddresses返回的地址放到下拉框中
    for (const tcpServerAddress &address : getAvailableNetworkAddresses())
    {
        // qDebug() << address.name << ":" << address.address.toString();
        ui->addressComboBox->addItem(address.name + ": " + address.address.toString(), QVariant::fromValue(address));
    }
}

tcpServer::~tcpServer()
{
    delete ui;
}

void tcpServer::on_listenButton_clicked()
{
    // 先关闭已开启的服务器 清除配置
    if (qtcpServer->isListening())
    {
        qtcpServer->close();
    }

    // 获取下拉框中选中的地址
    QHostAddress address = ui->addressComboBox->currentData().value<tcpServerAddress>().address;

    // 如果下拉框中没有选中地址 则使用第一个地址
    if (address.isNull())
    {
        address = ui->addressComboBox->itemData(0).value<tcpServerAddress>().address;
    }

    qDebug() << "address:" << address.toString();
    qtcpServer->listen(address, ui->portEdit->text().toInt());
    if (qtcpServer->isListening())
    {
        qDebug() << "tpc server: listen success";

        // 获取本地地址和端口
        QString localAddress = qtcpServer->serverAddress().toString();
        quint16 localPort = qtcpServer->serverPort();

        qDebug() << "服务器实际监听地址:" << localAddress;
        qDebug() << "服务器实际监听端口:" << localPort;
    }
    else
    {
        qDebug() << "tpc server: listen fail";
    }

    connect(qtcpServer, &QTcpServer::newConnection, this, &tcpServer::on_newConnection);
}

void tcpServer::on_newConnection()
{
    qDebug() << "tpc server: new connection";

    qtcpSocket = qtcpServer->nextPendingConnection();

    connect(qtcpSocket, &QTcpSocket::readyRead, this, &tcpServer::readData);
}

void tcpServer::readData()
{
    // 获取数据
    QString data = QString::fromUtf8(qtcpSocket->readAll());
    qDebug() << "tpc server: read: " << data;
    ui->recvTextEdit->appendPlainText(data);
}

void tcpServer::on_sendButton_clicked()
{
    QString data = ui->sendPlainTextEdit->toPlainText();
    qDebug() << "tpc server: send: " << data;
    qtcpSocket->write(data.toUtf8());
}

void tcpServer::on_backButton_clicked()
{
    this->parentWidget()->show();
    this->close();
}
