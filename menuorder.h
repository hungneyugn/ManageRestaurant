#ifndef MENUORDER_H
#define MENUORDER_H

#include <QMainWindow>
#include "boughtitem.h"
#include "item.h"
#include <vector>
#include <QCloseEvent>
#include "table.h"
#include "employeewindow.h"
#include "mainwindow.h"
#include "QLabel"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QScreen"
#include <QTableWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "item.h"
#include <QHeaderView>
#include <vector>
#include "staff.h"
#include "mainwindow.h"
#include "employeewindow.h"
#include "QMessageBox"

namespace Ui {
class menuorder;
}

class menuorder : public QMainWindow
{
    Q_OBJECT

public:
    explicit menuorder(employeeWindow *parent = nullptr,Table *table = nullptr);
    ~menuorder();

private:
    employeeWindow *parent_copy;
    Table *table;
    Ui::menuorder *ui;
    std::vector <Item> listitem;
    std::vector <BoughtItem> listboughtitem;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MENUORDER_H
