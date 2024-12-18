#include "second.h"
#include "ui_second.h"
#include <QDebug>

second::second(QWidget *parent) : QMainWindow(parent),
                                  ui(new Ui::second)
{
    ui->setupUi(this);
}

second::~second()
{
    delete ui;
}

void second::on_backButton_clicked()
{
    qDebug() << "on_backButton_clicked";

    // 显示第一个窗口
    this->parentWidget()->show();

    // 隐藏当前窗口
    this->close();
}
