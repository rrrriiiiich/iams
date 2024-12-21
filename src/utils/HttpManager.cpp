#include "HttpManager.h"

HttpManager::HttpManager()
{
  manager = new QNetworkAccessManager();

  // 打印支持的网络请求
  qDebug() << "Supported request methods:" << manager->supportedSchemes().join(", ");
}

HttpManager::~HttpManager()
{
  // 确保所有正在进行的请求都完成了
  QEventLoop loop;
  QObject::connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
  loop.exec();
  manager->deleteLater();
}

QNetworkReply *HttpManager::send(QUrl url, const requestOptions &options)
{
  qDebug() << "Sending request to:" << url.toString();
  QNetworkRequest request;
  request.setUrl(url);

  // 解析 https 链接
  QSslConfiguration cfg = request.sslConfiguration();
  cfg.setPeerVerifyMode(QSslSocket::VerifyNone);
  cfg.setProtocol(QSsl::AnyProtocol);
  request.setSslConfiguration(cfg);

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
    qDebug() << "method: Invalid method!";
    break;
  }

  this->waitForResponse(reply);

  return reply;
}

void HttpManager::setContentTypeHeader(QNetworkRequest &request, HttpContentType contentType)
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
    qDebug() << "setContentTypeHeader: Invalid content type!";
    break;
  }
}

void HttpManager::waitForResponse(QNetworkReply *reply)
{
  QEventLoop loop;
  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();
}

void HttpManager::saveImageToFile(QNetworkReply *reply, const QString &filename)
{
  QFile file(filename);
  if (file.open(QIODevice::WriteOnly))
  {
    // 打印图片的fileName
    qDebug() << "fileName: " << reply->request().url().fileName();
    file.write(reply->readAll());
    file.close();
    qDebug() << "file saved to:" << filename;
  }
}
