#ifndef tcpServer_H
#define tcpServer_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
// #include <QVariant>
#include "getAvailNwkAddrs.h"
#include "Logger.h"
#include "AvailNwkAddrCB.h"

namespace Ui
{
    class tcpServer;
}

class tcpServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit tcpServer(QWidget *parent = nullptr);
    ~tcpServer();

private slots:
    void on_listenButton_clicked();

    void on_newConnection();

    void readData();

    void on_sendButton_clicked();

    void on_backButton_clicked();

private:
    Ui::tcpServer *ui;

    QTcpServer *qtcpServer;
    QTcpSocket *qtcpSocket;

    AvailNwkAddrCB *availNwkAddrCB;
};

#endif // tcpServer_H
