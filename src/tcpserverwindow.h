#ifndef TCPSERVERWINDOW_H
#define TCPSERVERWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui
{
    class tcpServerWindow;
}

class tcpServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit tcpServerWindow(QWidget *parent = nullptr);
    ~tcpServerWindow();

private slots:
    void on_listenButton_clicked();

    void on_newConnection();

    void readData();

    void on_sendButton_clicked();

private:
    Ui::tcpServerWindow *ui;

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
};

#endif // TCPSERVERWINDOW_H
