#ifndef SECOND_H
#define SECOND_H

#include <QMainWindow>
#include <QDebug>

namespace Ui
{
    class second;
}

/**
 * @brief second 类定义了一个继承自 QMainWindow 的窗口，用于显示第二个界面
 */
class second : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数，初始化 second 窗口
     * @param parent 父窗口指针，默认为 nullptr
     */
    explicit second(QWidget *parent = nullptr);

    /**
     * @brief 析构函数，释放 second 窗口占用的资源
     */
    ~second();

private slots:
    /**
     * @brief 当返回按钮被点击时调用的槽函数
     * 该函数会关闭当前窗口并返回上一个窗口
     */
    void on_backButton_clicked();

private:
    Ui::second *ui; // 指向 second 窗口的 UI 类的指针
};

#endif // SECOND_H
