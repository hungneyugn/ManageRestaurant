#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>

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

private:
    Ui::ManagerWindow *ui;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MANAGERWINDOW_H
