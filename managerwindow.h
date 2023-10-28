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
    QString image_add;

protected:
    void closeEvent(QCloseEvent *event);
    void uploadImage();
//    void on_btn_save_clicked();
//    void on_btn_add_clicked();
private slots:
    void on_btn_add_clicked();
    void on_btn_save_clicked();
};

#endif // MANAGERWINDOW_H
