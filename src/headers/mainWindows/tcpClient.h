#ifndef tcpClient_H
#define tcpClient_H

#include <QMainWindow>
#include <QTcpSocket>

#include "Logger.h"

namespace Ui
{
    class tcpClient;
}

/**
 * @brief tcpClient 类定义了一个继承自 QMainWindow 的窗口，用于显示第二个界面
 */
class tcpClient : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数，初始化 tcpClient 窗口
     * @param parent 父窗口指针，默认为 nullptr
     */
    explicit tcpClient(QWidget *parent = nullptr);

    /**
     * @brief 析构函数，释放 tcpClient 窗口占用的资源
     */
    ~tcpClient();

private slots:
    /**
     * @brief 当返回按钮被点击时调用的槽函数
     * 该函数会关闭当前窗口并返回上一个窗口
     */
    void on_backButton_clicked();

    /**
     * @brief 当连接按钮被点击时调用的槽函数
     */
    void on_connectButton_clicked();

    /**
     * @brief 当发送按钮被点击时调用的槽函数
     */
    void on_sendButton_clicked();

    void readData();

private:
    Ui::tcpClient *ui; // 指向 tcpClient 窗口的 UI 类的指针
    QTcpSocket *qtcpSocket;
};

#endif // tcpClient_H
