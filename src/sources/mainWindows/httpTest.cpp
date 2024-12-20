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

    reply->deleteLater();

    QNetworkReply *reply2 = manager->sendRequest(QUrl("https://api.seniverse.com/v3/weather/now.json?key=Sklo5n7_p1T6c_AcV&location=%E5%B9%BF%E5%B7%9E&language=zh-Hans&unit=c"));

    if (reply2->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply2->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isNull() && jsonDoc.isObject())
        {
            QJsonObject jsonObj = jsonDoc.object();
            ui->showAreaLabel->setText(QString(jsonObj.value("results").toString()));

            SYSTEMLog() << "JSON Object:" << QString::fromUtf8(jsonDoc.toJson());
            ui->showAreaLabel->setText(QString::fromUtf8(jsonDoc.toJson()));
        }
        else
        {
            SYSTEMLog() << "Failed to parse JSON!";
        }
    }
    else
    {
        SYSTEMLog() << "Error:" << reply2->errorString();
    }

    reply2->deleteLater();
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
