#ifndef HTTPTEST_H
#define HTTPTEST_H

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
    class httpTest;
}

class httpTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit httpTest(QWidget *parent = nullptr);
    ~httpTest();

private:
    Ui::httpTest *ui;

    void getRequest();

private slots:
    void on_getRequestFinished();
    void on_requestButton_clicked();
    void on_showButton_clicked();
};

#endif // HTTPTEST_H
