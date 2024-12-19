#include "sendRequest.h"

void saveImageToFile(QNetworkReply *reply, const QString &filename)
{
  QFile file(filename);
  if (file.open(QIODevice::WriteOnly))
  {
    file.write(reply->readAll());
    file.close();
    qDebug() << "sendRequest: Image saved to:" << filename;
  }
  else
  {
    qDebug() << "sendRequest: Failed to save image!";
  }
}

void setContentTypeHeader(QNetworkRequest &request, HttpContentType contentType)
{
  switch (contentType)
  {
  case HttpContentType::JSON:
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    break;
  case HttpContentType::IMAGE:
    request.setHeader(QNetworkRequest::ContentTypeHeader, "image/png");
    break;
  default:
    break;
  }
}

void waitForResponseWithCallback(QNetworkReply *reply, std::function<void(QNetworkReply *)> callback)
{
  QEventLoop loop;
  QObject::connect(reply, &QNetworkReply::finished, [&]()
                   {
    callback(reply);
    loop.quit(); });
  loop.exec();
}

void handleNetworkResponse(QNetworkReply *reply)
{
  if (reply->error() == QNetworkReply::NoError)
  {
    if (reply->header(QNetworkRequest::ContentTypeHeader).toString().contains("image"))
    {
      saveImageToFile(reply, "test.png");
    }
  }
  else
  {
    qDebug() << "sendRequest: Error:" << reply->errorString();
  }
}

void sendRequest(QUrl url, const requestOptions &options)
{
  SYSTEMLog() << "Sending request to:" << url.toString();
  QNetworkRequest request;
  request.setUrl(url);

  QNetworkAccessManager *manager = new QNetworkAccessManager();

  setContentTypeHeader(request, options.contentType);

  QNetworkReply *reply = nullptr;

  switch (options.method)
  {
  case HttpMethod::GET:
    reply = manager->get(request);
    break;
  case HttpMethod::POST:
    // reply = manager->post(request, options.body);
    break;
  default:
    qDebug() << "sendRequest: Invalid method!";
    break;
  }

  waitForResponseWithCallback(reply, handleNetworkResponse);

  reply->deleteLater();
}
