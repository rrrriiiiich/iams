#include "serialPortTest.h"
#include "ui_serialPortTest.h"

serialPortTest::serialPortTest(QWidget *parent) : QMainWindow(parent),
                                                  ui(new Ui::serialPortTest)
{
    ui->setupUi(this);

    if (!QFile::exists("/dev/ttySAC2"))
    {
        Log() << "串口设备 /dev/ttySAC2 不存在";
        QMessageBox::information(this, "提示", "串口设备不存在");
        return;
    }

    // 创建串口对象，设置串口设备为/dev/ttySAC0
    serialPort = new QSerialPort("/dev/ttySAC2", this);
    // 设置串口名称为/dev/ttySAC0
    serialPort->setPortName("/dev/ttySAC2");
    // 设置波特率为115200
    serialPort->setBaudRate(QSerialPort::Baud115200);
    // 设置数据位为8位
    serialPort->setDataBits(QSerialPort::Data8);
    // 设置校验位为无校验
    serialPort->setParity(QSerialPort::NoParity);
    // 设置停止位为1位
    serialPort->setStopBits(QSerialPort::OneStop);
    // 设置流控制为无流控制
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    // 打开串口
    if (serialPort->open(QIODevice::ReadWrite))
    {
        Log() << "open success";
        QMessageBox::information(this, "提示", "串口打开成功");
    }
    else
    {
        Log() << "open failed";
        QMessageBox::information(this, "提示", "串口打开失败");
    }

    connect(serialPort, &QSerialPort::readyRead, this, &serialPortTest::on_readyRead);
}

void serialPortTest::on_readyRead()
{
    // 读取串口数据
    QByteArray data = serialPort->readAll();
    // 将数据转换为QString
    QString str = QString(data);
    Log() << serialPort->portName() << ": " << str;
    ui->recvPlainTextEdit->appendPlainText(serialPort->portName() + ": " + str);
}

serialPortTest::~serialPortTest()
{
    delete ui;
    serialPort->close();
    delete serialPort;
}
