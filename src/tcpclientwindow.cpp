#include "tcpclientwindow.h"
#include "ui_tcpclientwindow.h"
#include <QDebug>
#include <QTcpSocket>

/**
 * @brief tcpclientwindow 类的构造函数，初始化 tcpclientwindow 窗口
 * @param parent 父窗口指针，默认为 nullptr
 */
tcpClientWindow::tcpClientWindow(QWidget *parent) : QMainWindow(parent),
                                                    ui(new Ui::tcpClientWindow)
{
    // 初始化 UI
    ui->setupUi(this);

    // 创建 TCP 连接
    tcpSocket = new QTcpSocket(this);

    // 连接槽函数
    connect(tcpSocket, &QTcpSocket::readyRead, this, &tcpClientWindow::readData);

    // 方便调试 将edit的内容设置默认值
    // ui->addressEdit->setText("192.168.1.159");
    ui->addressEdit->setText("127.0.0.1");
    ui->portEdit->setText("3777");

    ui->sendEdit->setText("你好 服务端");
}

/**
 * @brief tcpclientwindow 类的析构函数，释放 tcpclientwindow 窗口占用的资源
 */
tcpClientWindow::~tcpClientWindow()
{
    // 释放 UI 资源
    delete ui;
}

/**
 * @brief 当返回按钮被点击时调用的槽函数
 * 该函数会关闭当前窗口并返回上一个窗口
 */
void tcpClientWindow::on_backButton_clicked()
{
    qDebug() << "on_backButton_clicked";

    // 显示第一个窗口
    this->parentWidget()->show();

    // 隐藏当前窗口
    this->close();
}

void tcpClientWindow::on_connectButton_clicked()
{
    QString address = ui->addressEdit->text().trimmed();
    int port = ui->portEdit->text().trimmed().toInt();
    // 创建 TCP 连接
    tcpSocket->connectToHost(address, port);
    qDebug() << "connect to host";
}

void tcpClientWindow::on_sendButton_clicked()
{
    // 发送数据
    tcpSocket->write(ui->sendEdit->text().trimmed().toUtf8());
    qDebug() << "send data";
}

void tcpClientWindow::readData()
{
    // ui->recvLabel->setText(tcpSocket->readAll());
    ui->recvPlainTextEdit->appendPlainText(tcpSocket->readAll());
    qDebug() << "read data";
}
