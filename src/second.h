#ifndef SECOND_H
#define SECOND_H

#include <QMainWindow>
#include <QDebug>

namespace Ui
{
    class second;
}

class second : public QMainWindow
{
    Q_OBJECT

public:
    explicit second(QWidget *parent = nullptr);
    ~second();

private slots:
    /**
     * @brief 当返回按钮被点击时调用的槽函数
     */
    void on_backButton_clicked();

private:
    Ui::second *ui;
};

#endif // SECOND_H
