#include "iams.h"
#include "ui_iams.h"
#include <QDebug>
#include <QMovie>

/**
 * @brief iams 类的构造函数
 * @param parent 父窗口指针，默认为 nullptr
 */
iams::iams(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::iams)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie("F://Embedded//Transportlayertraining//QT//iams//pic//lildog.gif");
    movie->start();
    ui->lildogLabel->setMovie(movie);
    // 按图片比例缩小
    ui->lildogLabel->setScaledContents(true);

    S1 = new second(this);
    TcpServer = new tcpServerWindow(this);

    // 默认设置用户名和密码
    ui->usernameLineEdit->setText("admin");
    ui->passwordLineEdit->setText("123456");

    TcpServer->show();
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
    // 获取并去除首尾空格，防止用户误输入空格导致登录失败
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text().trimmed();

    // 添加输入验证，避免空用户名或密码
    if (username.isEmpty() || password.isEmpty())
    {
        qDebug() << "用户名或密码不能为空";
        return;
    }

    // 使用常量存储凭据，便于后期维护和修改
    const QString VALID_USERNAME = "admin";
    const QString VALID_PASSWORD = "123456";

    if (username == VALID_USERNAME && password == VALID_PASSWORD)
    {
        qDebug() << "登录成功";

        // 先显示新窗口再隐藏当前窗口，避免界面闪烁
        S1->show();
        this->hide();
    }
    else
    {
        qDebug() << "登录失败：用户名或密码错误";
    }
}
