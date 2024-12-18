#ifndef TCPCLIENTWINDOW_H
#define TCPCLIENTWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpSocket>

namespace Ui
{
    class tcpClientWindow;
}

/**
 * @brief tcpClientWindow 类定义了一个继承自 QMainWindow 的窗口，用于显示第二个界面
 */
class tcpClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数，初始化 tcpClientWindow 窗口
     * @param parent 父窗口指针，默认为 nullptr
     */
    explicit tcpClientWindow(QWidget *parent = nullptr);

    /**
     * @brief 析构函数，释放 tcpClientWindow 窗口占用的资源
     */
    ~tcpClientWindow();

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
    Ui::tcpClientWindow *ui; // 指向 tcpClientWindow 窗口的 UI 类的指针
    QTcpSocket *tcpSocket;
};

#endif // TCPCLIENTWINDOW_H
