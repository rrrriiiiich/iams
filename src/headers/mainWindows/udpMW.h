#ifndef UDPMW_H
#define UDPMW_H

#include <QMainWindow>
#include <QUdpSocket>

#include "systemLog.h"

namespace Ui
{
    class udpMW;
}

class udpMW : public QMainWindow
{
    Q_OBJECT

public:
    explicit udpMW(QWidget *parent = nullptr);
    ~udpMW();

private slots:
    void on_backButton_clicked();

    void on_bindButton_clicked();

    void on_sendButton_clicked();

    void on_readData();

private:
    Ui::udpMW *ui;

    QUdpSocket *udpsocket;
};

#endif // UDPMW_H
