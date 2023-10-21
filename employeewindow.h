#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QMainWindow>

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
};

#endif // EMPLOYEEWINDOW_H
