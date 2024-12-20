#include "httpTest.h"
#include "ui_httpTest.h"

httpTest::httpTest(QWidget *parent) : QMainWindow(parent),
                                      ui(new Ui::httpTest)
{
    ui->setupUi(this);

    manager = new NetworkManager();
}

httpTest::~httpTest()
{
    delete ui;
}

void httpTest::on_requestButton_clicked()
{
    SYSTEMLog() << "on_requestButton_clicked";
    // 获取url
    QUrl url = ui->urlEdit->text();
    SYSTEMLog() << "url: " << url;
    // 发送请求获取响应
    QNetworkReply *reply = manager->sendRequest(url, {HttpMethod::GET, HttpContentType::IMAGE});

    if (reply->error() == QNetworkReply::NoError)
    {
        if (reply->header(QNetworkRequest::ContentTypeHeader).toString().contains("image"))
        {
            manager->saveImageToFile(reply, "test.png");
        }
    }
    else
    {
        SYSTEMLog() << "Error:" << reply->errorString();
    }
}

void httpTest::on_showButton_clicked()
{
    SYSTEMLog() << "on_showButton_clicked";
    QImage image("test.png");
    ui->showAreaLabel->setPixmap(QPixmap::fromImage(image));
}

void httpTest::on_backButton_clicked()
{
    // 显示第一个窗口
    this->parentWidget()->show();

    // 隐藏当前窗口
    this->close();
}
