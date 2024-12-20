#include "getAvailableNetworkAddresses.h"

QList<availableServerAddress> getAvailableNetworkAddresses()
{
  // 定义结构体保存筛选后的结果
  QList<availableServerAddress> addresses;

  QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
  for (const QNetworkInterface &interface : interfaces)
  {
    // 过滤掉无效的网络接口
    if (!interface.isValid() || interface.flags().testFlag(QNetworkInterface::IsLoopBack))
      continue;

    QList<QNetworkAddressEntry> entries = interface.addressEntries();
    for (const QNetworkAddressEntry &entry : entries)
    {
      QHostAddress address = entry.ip();
      if (!address.isNull())
      {
        // qDebug() << interface.humanReadableName() << " - Address:" << address.toString();
        addresses.append({interface.humanReadableName(), address});
      }
    }
  }

  return addresses;
}
