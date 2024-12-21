#include "udpMW.h"
#include "ui_udpMW.h"

udpMW::udpMW(QWidget *parent) : QMainWindow(parent),
                                ui(new Ui::udpMW)
{
    ui->setupUi(this);

    udpsocket = new QUdpSocket(this);

    connect(udpsocket, &QUdpSocket::readyRead, this, &udpMW::on_readData);
}

udpMW::~udpMW()
{
    delete ui;
}

void udpMW::on_backButton_clicked()
{
    this->parentWidget()->show();
    this->close();
}

void udpMW::on_bindButton_clicked()
{

    // 版本一：绑定端口为 50000
    // udpsocket->bind(ui->portEdit->text().toInt());
    // // 版本二：指定ip地址和端口进行绑定
    // 先解除绑定
    udpsocket->close();
    // 绑定
    udpsocket->bind(QHostAddress(ui->addressEdit->text()), ui->portEdit->text().toInt());
    qDebug() << "bind: " << ui->addressEdit->text() << ":" << ui->portEdit->text();
    ui->recvPlainTextEdit->appendPlainText(QString("[%1:%2] %3").arg(ui->addressEdit->text()).arg(ui->portEdit->text()).arg("bind success"));
}

void udpMW::on_readData()
{
    // 获取数据
    QByteArray datagram;
    datagram.resize(udpsocket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    // 读取数据包
    qint64 size = udpsocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

    // 检查socket错误
    if (udpsocket->error() != QAbstractSocket::UnknownSocketError)
    {
        QString errorMsg = QString("network error: %1").arg(udpsocket->errorString());
        qDebug() << errorMsg;
        ui->recvPlainTextEdit->appendPlainText(errorMsg);
    }

    // 检查数据包大小
    if (size <= 0)
    {
        qDebug() << "size <= 0";
    }

    // 正常数据包处理
    qDebug() << "receive from" << sender.toString() << ":" << senderPort;
    qDebug() << "receive:" << datagram;
    ui->recvPlainTextEdit->appendPlainText(
        QString("[%1:%2] %3").arg(sender.toString()).arg(senderPort).arg(QString(datagram)));
}

void udpMW::on_sendButton_clicked()
{
    QByteArray datagram = ui->sendEdit->text().toUtf8();
    udpsocket->writeDatagram(datagram, datagram.size(), QHostAddress(ui->sendAdderssEdit->text()), ui->sendPortEdit->text().toInt());
    qDebug() << "send: " << datagram;

    ui->recvPlainTextEdit->appendPlainText(QString("[send to %1:%2] %3").arg(ui->sendAdderssEdit->text()).arg(ui->sendPortEdit->text()).arg(QString(datagram)));
}
