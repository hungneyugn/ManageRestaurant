#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QMainWindow>
#include "staff.h"
namespace Ui {
class employeeWindow;
}

class employeeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit employeeWindow(QWidget *parent = nullptr);
    ~employeeWindow();

private:
    Ui::employeeWindow *ui;
    Staff* staff = new Staff;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // EMPLOYEEWINDOW_H
