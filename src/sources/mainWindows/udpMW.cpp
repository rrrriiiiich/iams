#include "udpMW.h"
#include "ui_udpMW.h"

udpMW::udpMW(QWidget *parent) : QMainWindow(parent),
                                ui(new Ui::udpMW)
{
    ui->setupUi(this);

    udpsocket = new QUdpSocket(this);
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
    udpsocket->bind(QHostAddress(ui->addressEdit->text()), ui->portEdit->text().toInt());
    qDebug() << "bind: " << ui->addressEdit->text() << ":" << ui->portEdit->text();

    connect(udpsocket, &QUdpSocket::readyRead, this, &udpMW::on_readData);
}

void udpMW::on_readData()
{
    // 获取数据
    QByteArray datagram;
    datagram.resize(udpsocket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    udpsocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
    qDebug() << "read: " << datagram;
    ui->recvPlainTextEdit->appendPlainText(sender.toString() + ":" + QString::number(senderPort) + ": " + datagram);
}

void udpMW::on_sendButton_clicked()
{
    QByteArray datagram = ui->sendEdit->text().toUtf8();
    udpsocket->writeDatagram(datagram, datagram.size(), QHostAddress(ui->sendAdderssEdit->text()), ui->sendPortEdit->text().toInt());
    qDebug() << "send: " << datagram;
}
