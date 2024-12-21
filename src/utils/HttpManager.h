
#ifndef SENDREQUEST_H
#define SENDREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QFile>
#include "SystemLogger.h"
#include <QUrl>

#include "SystemLogger.h"

/**
 * @brief HTTP请求方法枚举
 */
enum class HttpMethod
{
  GET,
  POST
};

/**
 * @brief HTTP内容类型枚举
 */
enum class HttpContentType
{
  JSON,
  IMAGE
};

/**
 * @brief 请求选项结构体
 */
struct requestOptions
{
  HttpMethod method;
  HttpContentType contentType;

  requestOptions(HttpMethod method, HttpContentType contentType) : method(method), contentType(contentType) {}
};

/**
 * @brief 网络请求管理类
 *
 * 该类负责处理HTTP网络请求的发送和接收
 */
class HttpManager
{
public:
  /**
   * @brief 构造函数
   */
  HttpManager();

  /**
   * @brief 析构函数
   */
  ~HttpManager();

  /**
   * @brief 发送网络请求
   * @param url 请求URL
   * @param options 请求选项
   * @return QNetworkReply* 网络响应对象
   */
  QNetworkReply *send(QUrl url, const requestOptions &options = requestOptions(HttpMethod::GET, HttpContentType::JSON));

  /**
   * @brief 将图片保存到文件
   * @param reply 网络响应对象
   * @param filename 保存的文件名
   */
  void saveImageToFile(QNetworkReply *reply, const QString &filename);

private:
  QNetworkAccessManager *manager;

  /**
   * @brief 设置请求的Content-Type头
   * @param request 网络请求对象
   * @param contentType 内容类型
   */
  void setContentTypeHeader(QNetworkRequest &request, HttpContentType contentType);

  /**
   * @brief 等待网络响应完成
   * @param reply 网络响应对象
   */
  void waitForResponse(QNetworkReply *reply);
};

#endif // SENDREQUEST_H
