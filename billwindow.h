#ifndef BILLWINDOW_H
#define BILLWINDOW_H

#include <QMainWindow>
#include "table.h"
#include "vector"

namespace Ui {
class billwindow;
}

class billwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit billwindow(QWidget *parent = nullptr, Table *table = nullptr);
    ~billwindow();

private:
    Ui::billwindow *ui;
    Table *table = new Table();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // BILLWINDOW_H
