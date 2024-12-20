#ifndef HTTPTEST_H
#define HTTPTEST_H

#include <QMainWindow>

#include "sendRequest.h"
#include "systemLog.h"

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

    QUrl url;

    NetworkManager *manager;

private slots:
    void on_requestButton_clicked();
    void on_showButton_clicked();
    void on_backButton_clicked();
};

#endif // HTTPTEST_H
