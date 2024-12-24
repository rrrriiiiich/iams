#ifndef SERIALPORTTEST_H
#define SERIALPORTTEST_H

#include <QMainWindow>
#include <QMessageBox>

#include <QSerialPort>

#include "Logger.h"

namespace Ui
{
    class serialPortTest;
}

class serialPortTest : public QMainWindow
{
    Q_OBJECT

public:
    explicit serialPortTest(QWidget *parent = nullptr);
    ~serialPortTest();

private slots:
    void on_readyRead();

private:
    Ui::serialPortTest *ui;

    QSerialPort *serialPort;
};

#endif // SERIALPORTTEST_H
