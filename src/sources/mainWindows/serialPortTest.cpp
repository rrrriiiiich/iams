#include "serialPortTest.h"
#include "ui_serialPortTest.h"

serialPortTest::serialPortTest(QWidget *parent) : QMainWindow(parent),
                                                  ui(new Ui::serialPortTest)
{
    ui->setupUi(this);

    // 创建串口对象，设置串口设备为/dev/ttySAC0
    serialPort = new QSerialPort("/dev/ttySAC2", this);
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
        QMessageBox::warning(this, "提示", "串口打开失败");
    }

    connect(serialPort, &QSerialPort::readyRead, this, &serialPortTest::on_readyRead);
}

void serialPortTest::on_readyRead()
{
}

serialPortTest::~serialPortTest()
{
    delete ui;
}
