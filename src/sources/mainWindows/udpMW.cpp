#include "udpMW.h"
#include "ui_udpMW.h"

udpMW::udpMW(QWidget *parent) : QMainWindow(parent),
                                ui(new Ui::udpMW)
{
    ui->setupUi(this);

    udpsocket = new QUdpSocket(this);

    connect(udpsocket, &QUdpSocket::readyRead, this, &udpMW::on_readData);

    availNwkAddrCB = new AvailNwkAddrCB(this);
    // 将addressComboBox位置替换为availNwkAddrCB
    ui->gridLayout->replaceWidget(ui->addressComboBox, availNwkAddrCB);
    ui->addressComboBox->setVisible(false);

    // 设置界面最大尺寸
    this->setMaximumSize(QSize(800, 480));

#ifndef _WIN32
    Log()
        << "new Buzz";
    buzz = new Buzz();

    Log() << "new Leds";
    leds = new Leds();
#endif
}

udpMW::~udpMW()
{
    delete ui;

    udpsocket->close();
    delete udpsocket;

#ifndef _WIN32
    delete buzz;
    delete leds;
#endif
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
    AvailNwkAddr addr = availNwkAddrCB->getSelectedAddress();
    udpsocket->bind(QHostAddress(addr.address), ui->portEdit->text().toInt());
    Log() << "bind: " << addr.address << ":" << ui->portEdit->text();
    ui->recvPlainTextEdit->appendPlainText(QString("[%1:%2] %3").arg(addr.address.toString()).arg(ui->portEdit->text()).arg("bind success"));
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
        Log() << errorMsg;
        ui->recvPlainTextEdit->appendPlainText(errorMsg);
    }

    // 检查数据包大小
    if (size <= 0)
    {
        Log() << "size <= 0";
    }

    // 正常数据包处理
    Log() << "receive from" << sender.toString() << ":" << senderPort;
    Log() << "receive:" << datagram;
    ui->recvPlainTextEdit->appendPlainText(
        QString("[%1:%2] %3").arg(sender.toString()).arg(senderPort).arg(QString(datagram)));

#ifndef _WIN32
    // 调用 buzz 函数
    if (QString(datagram) == "buzz on")
    {
        Log() << "buzz on";
        buzz->on();
    }
    else if (QString(datagram) == "buzz off")
    {
        Log() << "buzz off";
        buzz->off();
    }

    // 调用 leds 函数
    if (QString(datagram) == "led1 on")
    {
        leds->on(LED1);
    }
    else if (QString(datagram) == "led1 off")
    {
        leds->off(LED1);
    }
    else if (QString(datagram) == "led2 on")
    {
        leds->on(LED2);
    }
    else if (QString(datagram) == "led2 off")
    {
        leds->off(LED2);
    }
    else if (QString(datagram) == "led3 on")
    {
        leds->on(LED3);
    }
    else if (QString(datagram) == "led3 off")
    {
        leds->off(LED3);
    }
    else if (QString(datagram) == "led4 on")
    {
        leds->on(LED4);
    }
    else if (QString(datagram) == "led4 off")
    {
        leds->off(LED4);
    }
#endif
}

void udpMW::on_sendButton_clicked()
{
    QByteArray datagram = ui->sendEdit->text().toUtf8();
    udpsocket->writeDatagram(datagram, datagram.size(), QHostAddress(ui->sendAdderssEdit->text()), ui->sendPortEdit->text().toInt());
    Log() << "send: " << datagram;

    ui->recvPlainTextEdit->appendPlainText(QString("[send to %1:%2] %3").arg(ui->sendAdderssEdit->text()).arg(ui->sendPortEdit->text()).arg(QString(datagram)));
}
