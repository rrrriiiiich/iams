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
    // 创建应用程序对象
    QApplication a(argc, argv);

    // 创建主窗口
    iams w;

    // 显示主窗口
    w.show();

    // 运行应用程序并返回退出码
    return a.exec();
}
