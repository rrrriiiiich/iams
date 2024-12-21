#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QDebug>

namespace Ui
{
    class dashboard;
}

class dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit dashboard(QWidget *parent = nullptr);
    ~dashboard();

private:
    Ui::dashboard *ui;
};

#endif // DASHBOARD_H
