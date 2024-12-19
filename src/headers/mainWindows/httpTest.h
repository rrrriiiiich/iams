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
#include <QFile>
#include "sendRequest.h"

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

    void getRequest(QUrl url);

private:
    Ui::httpTest *ui;

    QNetworkAccessManager *request;
    QUrl url;

private slots:
    void on_requestButton_clicked();
    void on_showButton_clicked();
};

#endif // HTTPTEST_H
