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

    // 将getAvailNwkAddrs返回的地址放到下拉框中
    for (const AvailNwkAddr &address : getAvailNwkAddrs())
    {
        // Log() << address.name << ":" << address.address.toString();
        ui->addressComboBox->addItem(address.name + ": " + address.address.toString(), QVariant::fromValue(address));
    }

    // 连接槽函数
    connect(qtcpServer, &QTcpServer::newConnection, this, &tcpServer::on_newConnection);

    availNwkAddrCB = new AvailNwkAddrCB(this);
    // 将addressComboBox位置替换为availNwkAddrCB
    ui->gridLayout->replaceWidget(ui->addressComboBox, availNwkAddrCB);
    ui->addressComboBox->setVisible(false);

    // 设置界面最大尺寸
    this->setMaximumSize(QSize(800, 480));
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
    QHostAddress address = availNwkAddrCB->getSelectedAddress().address;
    qtcpServer->listen(address, ui->portEdit->text().toInt());
    if (qtcpServer->isListening())
    {
        Log() << "listen success";

        // 获取本地地址和端口
        QString localAddress = qtcpServer->serverAddress().toString();
        quint16 localPort = qtcpServer->serverPort();

        Log() << "服务器实际监听地址:" << localAddress;
        Log() << "服务器实际监听端口:" << localPort;
    }
    else
    {
        Log() << "listen fail";
    }
}

void tcpServer::on_newConnection()
{
    Log() << "new connection";

    qtcpSocket = qtcpServer->nextPendingConnection();

    connect(qtcpSocket, &QTcpSocket::readyRead, this, &tcpServer::readData);
}

void tcpServer::readData()
{
    // 获取数据
    QString data = QString::fromUtf8(qtcpSocket->readAll());
    Log() << "read: " << data;
    ui->recvTextEdit->appendPlainText(data);
}

void tcpServer::on_sendButton_clicked()
{
    QString data = ui->sendPlainTextEdit->toPlainText();
    Log() << "send: " << data;
    qtcpSocket->write(data.toUtf8());
}

void tcpServer::on_backButton_clicked()
{
    this->parentWidget()->show();
    this->close();
}
