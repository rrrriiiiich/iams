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
    serialPort = new QSerialPort(this);
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
    QString data = serialPort->readAll();
    qDebug() << "recv: " << data;
    Log() << serialPort->portName() << ": " << data;
    ui->recvPlainTextEdit->appendPlainText(serialPort->portName() + ": " + data);
}

serialPortTest::~serialPortTest()
{
    delete ui;
    serialPort->close();
    delete serialPort;
}

void serialPortTest::on_sendButton_clicked()
{
    // 获取发送数据
    Log() << "on_sendButton_clicked";
    QString str = ui->sendLineEdit->text().trimmed();
    serialPort->write(str.toUtf8());
    Log() << "send: " << str;
}

void serialPortTest::on_statusButton_clicked()
{
    // 获取状态
    Log() << "on_statusButton_clicked";
    serialPort->write("AT\r\n");
}

void serialPortTest::on_setNameButton_clicked()
{
    Log() << "on_setNameButton_clicked";
    serialPort->write("AT+NAMEJinJieBeWater\r\n");
}

void serialPortTest::on_getPwdButton_clicked()
{
    Log() << "on_getPwdButton_clicked";
    serialPort->write("AT+PIN\r\n");
}

void serialPortTest::on_setPwdButton_clicked()
{
    Log() << "on_setPwdButton_clicked";
    serialPort->write("AT+PWD123456\r\n");
}
