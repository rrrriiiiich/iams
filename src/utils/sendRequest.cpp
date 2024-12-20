#include "sendRequest.h"

NetworkManager::NetworkManager()
{
  manager = new QNetworkAccessManager();

  // 打印支持的网络请求
  SYSTEMLog() << "Supported request methods:" << manager->supportedSchemes().join(", ");
}

NetworkManager::~NetworkManager()
{
  // 确保所有正在进行的请求都完成了
  QEventLoop loop;
  QObject::connect(manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
  loop.exec();
  manager->deleteLater();
}

QNetworkReply *NetworkManager::sendRequest(QUrl url, const requestOptions &options)
{
  SYSTEMLog() << "Sending request to:" << url.toString();
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
    SYSTEMLog() << "method: Invalid method!";
    break;
  }

  this->waitForResponse(reply);

  return reply;
}

void NetworkManager::setContentTypeHeader(QNetworkRequest &request, HttpContentType contentType)
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
    SYSTEMLog() << "setContentTypeHeader: Invalid content type!";
    break;
  }
}

void NetworkManager::waitForResponse(QNetworkReply *reply)
{
  QEventLoop loop;
  QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();
}

void NetworkManager::saveImageToFile(QNetworkReply *reply, const QString &filename)
{
  QFile file(filename);
  if (file.open(QIODevice::WriteOnly))
  {
    // 打印图片的fileName
    SYSTEMLog() << "fileName: " << reply->request().url().fileName();
    file.write(reply->readAll());
    file.close();
    SYSTEMLog() << "file saved to:" << filename;
  }
}
