#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QFile>
#include <QEventLoop>
#include <functional>
#include "systemLog.h"

enum class HttpMethod
{
  GET,
  PUT,
  POST,
  DELETE
};

enum class HttpContentType
{
  JSON,
  XML,
  TEXT,
  IMAGE,
  MULTIPART
};

/**
 * HTTP请求的配置选项结构体
 * 包含请求方法、内容类型和文件路径等配置参数
 */
struct requestOptions
{
  HttpMethod method;
  HttpContentType contentType;
  QString filePath;

  // 构造函数，接受与初始化列表中提供的参数相匹配的参数
  requestOptions(HttpMethod m = HttpMethod::GET,
                 HttpContentType ct = HttpContentType::TEXT,
                 const QString &fp = "") : method(m), contentType(ct), filePath(fp) {}
};

/**
 * 将网络请求返回的图片数据保存到指定文件
 * @param reply 网络请求的回复对象指针
 * @param filename 要保存的文件名
 */
void saveImageToFile(QNetworkReply *reply, const QString &filename);

/**
 * 设置HTTP请求的Content-Type头部
 * @param request 网络请求对象的引用
 * @param contentType 内容类型枚举值，可以是JSON或IMAGE
 */
void setContentTypeHeader(QNetworkRequest &request, HttpContentType contentType);

/**
 * 等待网络请求完成并执行回调函数
 * @param reply 网络请求的回复对象指针
 * @param callback 请求完成后要执行的回调函数
 */
void waitForResponseWithCallback(QNetworkReply *reply, std::function<void(QNetworkReply *)> callback);

/**
 * 处理网络请求的响应
 * @param reply 网络请求的回复对象指针
 * 如果响应成功且内容类型为图片，则保存图片到文件
 * 如果响应失败，则输出错误信息
 */
void handleNetworkResponse(QNetworkReply *reply);

/**
 * 发送网络请求
 * @param url 请求的URL地址
 * @param options 请求选项，包含请求方法和内容类型等配置
 * 根据options中的配置发送GET请求，并处理响应结果
 */
void sendRequest(QUrl url, const requestOptions &options = {HttpMethod::GET, HttpContentType::IMAGE, "test.png"});
