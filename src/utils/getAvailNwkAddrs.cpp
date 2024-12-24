#include "getAvailNwkAddrs.h"

QList<AvailNwkAddr> getAvailNwkAddrs()
{
  // 定义结构体保存筛选后的结果
  QList<AvailNwkAddr> addresses;

  QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
  for (const QNetworkInterface &interface : interfaces)
  {
    // 过滤掉无效的网络接口
    if (!interface.isValid() || interface.flags().testFlag(QNetworkInterface::IsLoopBack))
      continue;

    // 过滤掉IPv6地址
    if (interface.addressEntries().first().ip().protocol() == QAbstractSocket::IPv6Protocol)
      continue;

    QList<QNetworkAddressEntry> entries = interface.addressEntries();
    for (const QNetworkAddressEntry &entry : entries)
    {
      QHostAddress address = entry.ip();
      if (!address.isNull())
      {
        // Log() << interface.humanReadableName() << " - Address:" << address.toString();
        addresses.append({interface.humanReadableName(), address});
      }
    }
  }

  return addresses;
}
