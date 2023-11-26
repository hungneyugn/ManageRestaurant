#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employeewindow.h"
#include "QStyleFactory"
#include "QFont"
#include "QScreen"
#include "managerwindow.h"
#include "manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(employeeWindow *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_employeeButton_clicked();

private:
    Ui::MainWindow *ui;
    employeeWindow* employeeWindow1 = nullptr;
};
#endif // MAINWINDOW_H
