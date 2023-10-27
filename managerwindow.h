#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include "manager.h"
#include <QTableWidget>
#include "QtWidgets"


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
    void openFolder();

signals:
    void buttonClicked();

private:
    Ui::ManagerWindow *ui;
    Manager *manager = new Manager;
    QTableWidget *tableItem;
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_btnAdd_clicked();
    void on_btnSave_clicked();
    void on_btnUpload_clicked();

};




#endif // MANAGERWINDOW_H
