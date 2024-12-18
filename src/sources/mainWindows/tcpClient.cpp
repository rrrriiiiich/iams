#include "tcpClient.h"
#include "ui_tcpClient.h"

/**
 * @brief tcpClient 类的构造函数，初始化 tcpClient 窗口
 * @param parent 父窗口指针，默认为 nullptr
 */
tcpClient::tcpClient(QWidget *parent) : QMainWindow(parent),
                                        ui(new Ui::tcpClient)
{
    // 初始化 UI
    ui->setupUi(this);

    // 创建 TCP 连接
    qtcpSocket = new QTcpSocket(this);

    // 连接槽函数
    connect(qtcpSocket, &QTcpSocket::readyRead, this, &tcpClient::readData);

    // 方便调试 将edit的内容设置默认值
    // ui->addressEdit->setText("192.168.1.159");
    ui->addressEdit->setText("127.0.0.1");
    ui->portEdit->setText("3777");

    ui->sendEdit->setText("你好 服务端");
}

/**
 * @brief tcpClient 类的析构函数，释放 tcpClient 窗口占用的资源
 */
tcpClient::~tcpClient()
{
    // 释放 UI 资源
    delete ui;
}

/**
 * @brief 当返回按钮被点击时调用的槽函数
 * 该函数会关闭当前窗口并返回上一个窗口
 */
void tcpClient::on_backButton_clicked()
{
    qDebug() << "on_backButton_clicked";

    // 显示第一个窗口
    this->parentWidget()->show();

    // 隐藏当前窗口
    this->close();
}

void tcpClient::on_connectButton_clicked()
{
    QString address = ui->addressEdit->text().trimmed();
    int port = ui->portEdit->text().trimmed().toInt();
    // 创建 TCP 连接
    qtcpSocket->connectToHost(address, port);
    qDebug() << "connect to host";
}

void tcpClient::on_sendButton_clicked()
{
    // 发送数据
    qtcpSocket->write(ui->sendEdit->text().trimmed().toUtf8());
    qDebug() << "send data";
}

void tcpClient::readData()
{
    // ui->recvLabel->setText(tcpSocket->readAll());
    ui->recvPlainTextEdit->appendPlainText(qtcpSocket->readAll());
    qDebug() << "read data";
}
