#include <QDebug>
// 包含客户端网络请求类
#include <QNetworkRequest>
// 包含客户端网络响应类
#include <QNetworkReply>
// 包含客户端网络请求管理器类
#include <QNetworkAccessManager>
#include <QFile>
#include <QEventLoop>

void sendRequest(QUrl url);
