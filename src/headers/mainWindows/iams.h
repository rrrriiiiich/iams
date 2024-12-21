#pragma once
#include "ui_iams.h"
#include "tcpClient.h"
#include "tcpServer.h"
#include "udpMW.h"
#include "dashboard.h"
#include "httpTest.h"
#include "Logger.h"

#include <QMainWindow>
#include <QMovie>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class iams;
}
QT_END_NAMESPACE

class iams : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数，初始化 iams 类的实例
     * @param parent 父窗口指针，默认为 nullptr
     */
    iams(QWidget *parent = nullptr);

    /**
     * @brief 析构函数，释放 iams 类实例所占用的资源
     */
    ~iams();

private slots:
    /**
     * @brief 当取消按钮被点击时调用的槽函数
     */
    void on_cancel_clicked();

    /**
     * @brief 当确认按钮被点击时调用的槽函数
     */
    void on_login_clicked();

    void on_tcpcServerBt_clicked();

    void on_tcpClientBt_clicked();

    void on_udpTestBt_clicked();

    void on_httpTestButton_clicked();

private:
    /**
     * @brief 指向 Ui_iams 类的指针，用于访问和操作界面元素
     */
    Ui::iams *ui;

    /**
     * @brief 指向 tcpClient 类的指针，用于管理和操作第二个窗口
     */
    tcpClient *TcpClient;

    /**
     * @brief 指向 tcpServer 类的指针，用于管理和操作 tcpServer 窗口
     */
    tcpServer *TcpServer;

    /**
     * @brief 指向 udpMW 类的指针，用于管理和操作 udpMW 窗口
     */
    udpMW *UdpMW;

    /**
     * @brief   指向 dashboard 类的指针，用于管理和操作 dashboard 窗口
     */
    dashboard *Dashboard;

    /**
     * @brief   指向 httpTest 类的指针，用于管理和操作 httpTest 窗口
     */
    httpTest *HttpTest;
};
