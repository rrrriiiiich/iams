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
