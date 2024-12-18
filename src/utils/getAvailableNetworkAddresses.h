#include <QDebug>
#include <QNetworkInterface>

struct tcpServerAddress
{
  QString name;
  QHostAddress address;
};

QList<tcpServerAddress> getAvailableNetworkAddresses();
