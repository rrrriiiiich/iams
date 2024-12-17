#include "iams.h"
#include "ui_iams.h"
#include <QDebug>

/**
 * @brief iams 类的构造函数
 * @param parent 父窗口指针，默认为 nullptr
 */
iams::iams(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::iams)
{
    ui->setupUi(this);

    S1 = new second(this);
}

/**
 * @brief iams 类的析构函数
 */
iams::~iams()
{
    delete ui;
}

/**
 * @brief 当取消按钮被点击时调用的槽函数
 */
void iams::on_cancel_clicked()
{
    qDebug() << "取消按钮槽函数";
    this->close();
}

void iams::on_login_clicked()
{
    qDebug() << "登录按钮槽函数";
    // 获取username 和 password 的值
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username == "admin" && password == "123456")
    {
        /* code */
        qDebug() << "登录成功";

        // 隐藏当前窗口
        this->hide();

        // 显示第二个窗口
        S1->show();
    }
    else
    {
        qDebug() << "登录失败";
    }
}
