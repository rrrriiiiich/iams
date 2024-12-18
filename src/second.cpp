#include "second.h"
#include "ui_second.h"
#include <QDebug>

/**
 * @brief second 类的构造函数，初始化 second 窗口
 * @param parent 父窗口指针，默认为 nullptr
 */
second::second(QWidget *parent) : QMainWindow(parent),
                                  ui(new Ui::second)
{
    // 初始化 UI
    ui->setupUi(this);
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
