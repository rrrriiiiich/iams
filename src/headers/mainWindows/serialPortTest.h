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

  void on_sendButton_clicked();

  void on_statusButton_clicked();

  void on_setNameButton_clicked();

  void on_getPwdButton_clicked();

  void on_setPwdButton_clicked();

  void on_backButton_clicked();

private:
  Ui::serialPortTest *ui;

  QSerialPort *serialPort;
};

#endif // SERIALPORTTEST_H
