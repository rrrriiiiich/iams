#ifndef AVAILNWKADDR_H
#define AVAILNWKADDR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>

#include "getAvailNwkAddrs.h"

namespace Ui
{
    class AvailNwkAddrCB;
}

class AvailNwkAddrCB : public QWidget
{
    Q_OBJECT

public:
    explicit AvailNwkAddrCB(QWidget *parent = nullptr);
    ~AvailNwkAddrCB();

    void selectedAddr(const AvailNwkAddr &addr);
    AvailNwkAddr getSelectedAddress() const;

private:
    Ui::AvailNwkAddrCB *ui;
    AvailNwkAddr currentSelectedAddress;
};
#endif // AVAILNWKADDR_H
