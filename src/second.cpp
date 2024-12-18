#include "second.h"
#include "ui_second.h"
#include <QDebug>
#include <QTcpSocket>

/**
 * @brief second 类的构造函数，初始化 second 窗口
 * @param parent 父窗口指针，默认为 nullptr
 */
second::second(QWidget *parent) : QMainWindow(parent),
                                  ui(new Ui::second)
{
    // 初始化 UI
    ui->setupUi(this);

    // 创建 TCP 连接
    tcpSocket = new QTcpSocket(this);

    // 连接槽函数
    connect(tcpSocket, &QTcpSocket::readyRead, this, &second::readData);

    // 方便调试 将edit的内容设置默认值
    ui->addressEdit->setText("192.168.1.153");
    ui->portEdit->setText("8080");

    ui->sendEdit->setText("你好 服务端");
}

/**
 * @brief second 类的析构函数，释放 second 窗口占用的资源
 */
second::~second()
{
    // 释放 UI 资源
    delete ui;
}

/**
 * @brief 当返回按钮被点击时调用的槽函数
 * 该函数会关闭当前窗口并返回上一个窗口
 */
void second::on_backButton_clicked()
{
    qDebug() << "on_backButton_clicked";

    // 显示第一个窗口
    this->parentWidget()->show();

    // 隐藏当前窗口
    this->close();
}

void second::on_connectButton_clicked()
{
    QString address = ui->addressEdit->text().trimmed();
    int port = ui->portEdit->text().trimmed().toInt();
    // 创建 TCP 连接
    tcpSocket->connectToHost(address, port);
}

void second::on_sendButton_clicked()
{
    // 发送数据
    tcpSocket->write(ui->sendEdit->text().trimmed().toUtf8());
}

void second::readData()
{
    // ui->recvLabel->setText(tcpSocket->readAll());
    ui->recvPlainTextEdit->appendPlainText(tcpSocket->readAll());
}
