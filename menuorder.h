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
