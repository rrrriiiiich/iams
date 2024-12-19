#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QDebug>
// 包含客户端网络请求类
#include <QNetworkRequest>
// 包含客户端网络响应类
#include <QNetworkReply>
// 包含客户端网络请求管理器类
#include <QNetworkAccessManager>

namespace Ui
{
    class dashboard;
}

class dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit dashboard(QWidget *parent = nullptr);
    ~dashboard();

private:
    Ui::dashboard *ui;
};

#endif // DASHBOARD_H
