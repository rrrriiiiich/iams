#ifndef UDPMW_H
#define UDPMW_H

#include <QMainWindow>

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

private:
    Ui::udpMW *ui;
};

#endif // UDPMW_H
