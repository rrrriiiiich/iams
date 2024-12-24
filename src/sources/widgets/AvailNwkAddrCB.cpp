#include "AvailNwkAddrCB.h"
#include "ui_AvailNwkAddrCB.h"

AvailNwkAddrCB::AvailNwkAddrCB(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::AvailNwkAddrCB)
{
    ui->setupUi(this);

    QList<AvailNwkAddr> availNwkAddrList = getAvailNwkAddrs();

    // 添加布局
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addWidget(new QLabel("可用网络地址："));
    // 添加下拉框
    QComboBox *comboBox = new QComboBox;
    for (const AvailNwkAddr &address : availNwkAddrList)
    {
        comboBox->addItem(address.name + ": " + address.address.toString(), QVariant::fromValue(address));
    }
    // 设置第一个选项为默认选项
    comboBox->setCurrentIndex(0);
    horizontalLayout->addWidget(comboBox);

    comboBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    // 设置宽度策略

    // 连接信号和槽
    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
            [=](int index)
            {
                AvailNwkAddr selectedAddr = comboBox->itemData(index).value<AvailNwkAddr>();
                // 设置当前选中的地址
                currentSelectedAddress = selectedAddr;
                // 触发回调函数
                this->selectedAddr(selectedAddr);
            });

    setLayout(horizontalLayout);
}

AvailNwkAddrCB::~AvailNwkAddrCB()
{
    delete ui;
}

void AvailNwkAddrCB::selectedAddr(const AvailNwkAddr &addr)
{
    Log() << addr.name << ":" << addr.address.toString();
}

AvailNwkAddr AvailNwkAddrCB::getSelectedAddress() const
{
    return currentSelectedAddress;
}
