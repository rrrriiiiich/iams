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

void httpTest::getRequest(QUrl url)
{
    qDebug() << "get request";
    // 创建一个 QNetworkRequest 对象，用于发送 HTTP 请求
    QNetworkRequest request;

    // 设置请求的 URL 和请求方法
    request.setUrl(url);
    // request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.0.0 Safari/537.36");
    // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 创建一个 QNetworkAccessManager 对象，用于管理网络请求
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // 创建一个 QNetworkReply 对象，用于接收响应
    QNetworkReply *reply = manager->get(request);

    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        // 保存图片到本地文件
        QFile file("c413eaf4-bfad-43bd-820b-538d5c7dcfd0.png");
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(reply->readAll());
            file.close();
            qDebug() << "httpTest: Image saved to:" << "c413eaf4-bfad-43bd-820b-538d5c7dcfd0.png";
        }
        else
        {
            qDebug() << "httpTest: Failed to save image!";
        }
    }
    else
    {
        qDebug() << "httpTest: Error:" << reply->errorString();
    }

    reply->deleteLater();

    // 避免重复连接
    disconnect(reply, &QNetworkReply::finished, this, &httpTest::on_getRequestFinished);
    connect(reply, &QNetworkReply::finished, this, &httpTest::on_getRequestFinished);
}

// http get 请求完成后的响应
void httpTest::on_getRequestFinished()
{
    // 获取响应的数据
    QByteArray data = qobject_cast<QNetworkReply *>(sender())->readAll();

    // 获取响应的状态码
    int statusCode = qobject_cast<QNetworkReply *>(sender())->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    // 打印响应的数据和状态码
    qDebug() << "httpTest: status code: " << statusCode;
    qDebug() << "httpTest: data: " << data;
}

void httpTest::on_requestButton_clicked()
{
    qDebug() << "httpTest: on_requestButton_clicked";
    // 获取url
    QUrl url = ui->urlEdit->text();
    qDebug() << "httpTest: url: " << url;
    // 发送请求获取响应
    getRequest(url);
}

void httpTest::on_showButton_clicked()
{
    qDebug() << "httpTest: on_showButton_clicked";
    // 从"c413eaf4-bfad-43bd-820b-538d5c7dcfd0.png"读取图片
    QImage image("c413eaf4-bfad-43bd-820b-538d5c7dcfd0.png");
    ui->showAreaLabel->setPixmap(QPixmap::fromImage(image));
}
