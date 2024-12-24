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
#ifndef _WIN32
    SerialPortTest = new serialPortTest(this);
#endif // _WIN32
    // 默认设置用户名和密码
    ui->usernameLineEdit->setText("admin");
    ui->passwordLineEdit->setText("123456");

    // 设置协议选择器内容
    ui->protocolComboBox->addItem("TCP 服务器");
    ui->protocolComboBox->addItem("TCP 客户端");
    ui->protocolComboBox->addItem("UDP 测试");
    ui->protocolComboBox->addItem("HTTP 测试");
#ifndef _WIN32
    ui->protocolComboBox->addItem("蓝牙串口测试");
#endif // _WIN32
    // 设置协议选择器默认选项
    ui->protocolComboBox->setCurrentIndex(0);
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
    QMessageBox::information(this, "提示", "再退出就没有页面啦！");
}

void iams::on_login_clicked()
{
    // 获取并去除首尾空格，防止用户误输入空格导致登录失败
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text().trimmed();

    // 添加输入验证，避免空用户名或密码
    if (username.isEmpty() || password.isEmpty())
    {
        Log() << "login failed: username or password is empty";
        return;
    }

    // 使用常量存储凭据，便于后期维护和修改
    const QString VALID_USERNAME = "admin";
    const QString VALID_PASSWORD = "123456";

    if (username == VALID_USERNAME && password == VALID_PASSWORD)
    {
        Log() << "login success";

        // 先显示新窗口再隐藏当前窗口，避免界面闪烁
        Dashboard->show();
        this->hide();
    }
    else
    {
        Log() << "login failed: username or password is wrong";
    }
}

void iams::on_goToTestButton_clicked()
{
    QString protocol = ui->protocolComboBox->currentText();

    Log() << "protocol:" << protocol;

    if (protocol == "TCP 服务器")
    {
        TcpServer->show();
    }
    else if (protocol == "TCP 客户端")
    {
        TcpClient->show();
    }
    else if (protocol == "UDP 测试")
    {
        UdpMW->show();
    }
    else if (protocol == "HTTP 测试")
    {
        HttpTest->show();
    }
#ifndef _WIN32
    else if (protocol == "蓝牙串口测试")
    {
        SerialPortTest->show();
    }
#endif // _WIN32
}
