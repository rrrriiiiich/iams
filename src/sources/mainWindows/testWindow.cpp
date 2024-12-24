#include "testWindow.h"
#include "ui_testWindow.h"

testWindow::testWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testWindow)
{
    ui->setupUi(this);
}

testWindow::~testWindow()
{
    delete ui;
}
