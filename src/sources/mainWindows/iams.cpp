#include "iams.h"
#include "ui_iams.h"

/**
 * @brief iams 类的构造函数
 * @param parent 父窗口指针，默认为 nullptr
 */
iams::iams(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::iams)
{
    ui->setupUi(this);

    QMovie *movie = new QMovie(":/pic/lildog.gif");
    ui->lildogLabel->setMovie(movie);
    movie->start();

    // 按图片比例缩小
    ui->lildogLabel->setScaledContents(true);

    TcpClient = new tcpClient(this);
    TcpServer = new tcpServer(this);
    UdpMW = new udpMW(this);
    Dashboard = new dashboard(this);
    HttpTest = new httpTest(this);

    // 默认设置用户名和密码
    ui->usernameLineEdit->setText("admin");
    ui->passwordLineEdit->setText("123456");
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
    this->hide();
}

void iams::on_login_clicked()
{
    // 获取并去除首尾空格，防止用户误输入空格导致登录失败
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text().trimmed();

    // 添加输入验证，避免空用户名或密码
    if (username.isEmpty() || password.isEmpty())
    {
        qDebug() << "login failed: username or password is empty";
        return;
    }

    // 使用常量存储凭据，便于后期维护和修改
    const QString VALID_USERNAME = "admin";
    const QString VALID_PASSWORD = "123456";

    if (username == VALID_USERNAME && password == VALID_PASSWORD)
    {
        qDebug() << "login success";

        // 先显示新窗口再隐藏当前窗口，避免界面闪烁
        Dashboard->show();
        this->hide();
    }
    else
    {
        qDebug() << "login failed: username or password is wrong";
    }
}

void iams::on_tcpcServerBt_clicked()
{
    TcpServer->show();
}

void iams::on_tcpClientBt_clicked()
{
    TcpClient->show();
}

void iams::on_udpTestBt_clicked()
{
    UdpMW->show();
}

void iams::on_httpTestButton_clicked()
{
    HttpTest->show();
}
