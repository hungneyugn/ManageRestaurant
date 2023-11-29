#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include "manager.h"
#include <QTableWidget>
#include "QPushButton"
#include "employeewindow.h"
#include "QScreen"
#include <QCloseEvent>
#include "mainwindow.h"
#include "manager.h"
#include "QString"
#include "string"
#include <iostream>
#include <fstream>
#include <sstream>
#include "QTextEdit"
#include <string>
#include <QFileDialog>
#include <QDir>
#include "QIcon"
#include "QLabel"
#include "QPixmap"
#include <cmath>
#include "QScreen"
#include "QMessageBox"
#include "staff.h"
#include "QStyleFactory"
#include "QHeaderView"
#include "QFont"
#include "QLocale"

namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr, employeeWindow *employee = nullptr);
    ~ManagerWindow();
    void closeEvent();
    QTableWidget *tableItem;

private:
    Ui::ManagerWindow *ui;
    Manager *manager = new Manager;
    QString image_add;
    QPushButton *newButton;
    employeeWindow *employee = nullptr;

protected:
    void closeEvent(QCloseEvent *event);
    void uploadImage();

private slots:
    void on_btn_add_clicked();
    void on_btn_save_clicked();
    void on_btn_delete_clicked();
    void on_btn_update_clicked();
};

#endif // MANAGERWINDOW_H
