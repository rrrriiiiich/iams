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
    qDebug() << "httpTest: on_requestButton_clicked";
    // 获取url
    QUrl url = ui->urlEdit->text();
    qDebug() << "httpTest: url: " << url;
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
        qDebug() << "sendRequest: Error:" << reply->errorString();
    }
}

void httpTest::on_showButton_clicked()
{
    qDebug() << "httpTest: on_showButton_clicked";
    QImage image("test.png");
    ui->showAreaLabel->setPixmap(QPixmap::fromImage(image));
}
