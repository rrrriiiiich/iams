#include "udpMW.h"
#include "ui_udpMW.h"

udpMW::udpMW(QWidget *parent) : QMainWindow(parent),
                                ui(new Ui::udpMW)
{
    ui->setupUi(this);
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
    qDebug() << "bind";
}

void udpMW::on_sendButton_clicked()
{
    qDebug() << "send";
}
