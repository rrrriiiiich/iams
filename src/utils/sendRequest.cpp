#include "sendRequest.h"

void sendRequest(QUrl url)
{
  qDebug() << "get request";
  // 创建一个 QNetworkRequest 对象，用于发送 HTTP 请求
  QNetworkRequest request;

  // 设置请求的 URL 和请求方法
  request.setUrl(url);
  // request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/103.0.0.0 Safari/537.36");
  // request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  // 创建一个 QNetworkAccessManager 对象，用于管理网络请求
  QNetworkAccessManager *manager = new QNetworkAccessManager();

  // 创建一个 QNetworkReply 对象，用于接收响应
  QNetworkReply *reply = manager->get(request);

  QEventLoop loop;
  QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
  loop.exec();

  if (reply->error() == QNetworkReply::NoError)
  {
    // 如果是图片 则保存到本地
    if (reply->header(QNetworkRequest::ContentTypeHeader).toString().contains("image"))
    {
      // 保存图片到本地文件
      QFile file("test.png");
      if (file.open(QIODevice::WriteOnly))
      {
        file.write(reply->readAll());
        file.close();
        qDebug() << "sendRequest: Image saved to:" << "test.png";
      }
      else
      {
        qDebug() << "sendRequest: Failed to save image!";
      }
    }
  }
  else
  {
    qDebug() << "sendRequest: Error:" << reply->errorString();
  }

  reply->deleteLater();
}
