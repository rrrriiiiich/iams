#ifndef GET_AVAILABLE_NETWORK_ADDRESSES_H
#define GET_AVAILABLE_NETWORK_ADDRESSES_H

#include <QDebug>
#include <QNetworkInterface>

/**
 * @brief 网络地址信息结构体
 * 用于存储网络接口名称和对应的IP地址
 */
struct tcpServerAddress
{
  QString name;         ///< 网络接口名称
  QHostAddress address; ///< IP地址
};

/**
 * @brief 获取系统中所有可用的网络地址
 * @return 返回包含网络接口名称和地址信息的列表
 * @details 该函数会过滤掉无效的网络接口和回环地址,
 *          只返回有效的网络接口地址信息
 */
QList<tcpServerAddress> getAvailableNetworkAddresses();

#endif // GET_AVAILABLE_NETWORK_ADDRESSES_H
