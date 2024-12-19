#include <QDebug>
#include <QNetworkInterface>

struct tcpServerAddress
{
  QString name;
  QHostAddress address;
};

Q_DECLARE_METATYPE(tcpServerAddress)

QList<tcpServerAddress> getAvailableNetworkAddresses();
