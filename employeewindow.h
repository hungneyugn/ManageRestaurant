#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QMainWindow>
#include "staff.h"
#include "QScreen"
#include <QCloseEvent>
#include "staff.h"
#include "table.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"
#include <QPushButton>
namespace Ui {
class employeeWindow;
}

class employeeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit employeeWindow(Staff *newStaff, QWidget *parent = nullptr);
    ~employeeWindow();

private:
    Ui::employeeWindow *ui;
public:
    Staff* staff = new Staff;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // EMPLOYEEWINDOW_H
