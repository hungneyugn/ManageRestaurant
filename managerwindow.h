#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include "manager.h"
#include <QTableWidget>

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr);
    ~ManagerWindow();
    void closeEvent();
    QTableWidget *tableItem;

private:
    Ui::ManagerWindow *ui;
    Manager *manager = new Manager;

protected:
    void closeEvent(QCloseEvent *event);
private slots:
};

#endif // MANAGERWINDOW_H
