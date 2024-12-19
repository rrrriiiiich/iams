#include "httpTest.h"
#include "ui_httpTest.h"

httpTest::httpTest(QWidget *parent) : QMainWindow(parent),
                                      ui(new Ui::httpTest)
{
    ui->setupUi(this);
}

httpTest::~httpTest()
{
    delete ui;
}

void httpTest::on_requestButton_clicked()
{
    qDebug() << "httpTest: on_requestButton_clicked";
    // 获取url
    QUrl url = ui->urlEdit->text();
    qDebug() << "httpTest: url: " << url;
    // 发送请求获取响应
    sendRequest(url, {});
}

void httpTest::on_showButton_clicked()
{
    qDebug() << "httpTest: on_showButton_clicked";
    QImage image("test.png");
    ui->showAreaLabel->setPixmap(QPixmap::fromImage(image));
}
