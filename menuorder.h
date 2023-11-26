#ifndef MENUORDER_H
#define MENUORDER_H

#include <QTableWidget>
#include <QHBoxLayout>

#include "QMessageBox"
#include "QLineEdit"
#include "QLocale"

#include "item.h"
#include "table.h"
#include "employeewindow.h"

#include "billwindow.h"

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
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MENUORDER_H
