#include "employeewindow.h"
#include "ui_employeewindow.h"

employeeWindow::employeeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employeeWindow)
{
    ui->setupUi(this);
}

employeeWindow::~employeeWindow()
{
    delete ui;
}
