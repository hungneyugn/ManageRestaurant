#ifndef BILLWINDOW_H
#define BILLWINDOW_H

#include <QMainWindow>
#include "employeewindow.h"
#include "table.h"
#include "vector"

namespace Ui {
class billwindow;
}

class billwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit billwindow(employeeWindow *parent = nullptr, Table *table = nullptr);
    ~billwindow();

private:
    Ui::billwindow *ui;
protected:
    Table *table = new Table();
    Staff *staff = new Staff();
    void closeEvent(QCloseEvent *event);
};

#endif // BILLWINDOW_H
