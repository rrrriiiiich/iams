#ifndef HTTPTEST_H
#define HTTPTEST_H

#include <QMainWindow>
#include <QDebug>
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

    NetworkManager *manager;

private slots:
    void on_requestButton_clicked();
    void on_showButton_clicked();
};

#endif // HTTPTEST_H
