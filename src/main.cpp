#include "iams.h"

#include <QApplication>
// #pragma comment(lib, "user32.lib")

/**
 * @brief 应用程序的入口点
 * @param argc 命令行参数个数
 * @param argv 命令行参数数组
 * @return 应用程序的退出状态
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // 创建 QApplication 对象，用于管理应用程序的事件循环
    iams w;                     // 创建 iams 窗口对象
    w.show();                   // 显示 iams 窗口
    return a.exec();            // 进入事件循环，等待用户操作并处理事件
}
