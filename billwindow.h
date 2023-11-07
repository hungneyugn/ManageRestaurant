#ifndef BILLWINDOW_H
#define BILLWINDOW_H

#include <QMainWindow>
#include "employeewindow.h"
#include "table.h"
#include "vector"
#include "QVBoxLayout"
#include "QPushButton"
#include "QTableWidgetItem"
#include "QHeaderView"
#include "QLabel"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"
#include "boughtitem.h"
#include "QScreen"

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
