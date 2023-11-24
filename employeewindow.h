#ifndef EMPLOYEEWINDOW_H
#define EMPLOYEEWINDOW_H

#include <QMainWindow>
#include "staff.h"
#include "QScreen"
#include <QCloseEvent>
#include "staff.h"
#include "table.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"
#include <QPushButton>

#define MAKE_TABLE(w, h, num, row, column, size, w_table, h_table)\
for (int j = 0; j < column; j++) {\
        if (j < column/2) {\
            for (int i = 0 + row * j; i < row * (j + 1) && i < num; i++) { \
                QPushButton* button = new QPushButton(ui->centralwidget); \
                button->setGeometry(w / 2 + ((j - column / 2) * (w_table + 10)), 100 + (h_table + 10) * (i - (row * j)),w_table, h_table); \
                button->setText(QString("Table %1").arg(QString::number(i + 1))); \
                QFont font = button->font(); \
                font.setBold(true); \
                font.setPointSize(size); \
                button->setFont(font); \
                button->setStyle(QStyleFactory::create("Fusion")); \
                button->setStyleSheet("QPushButton {" \
                                      "font-weight: bold;" \
                                      "border-radius: 10px ;" \
                                      "border: 1px solid black;" \
                                      "background-color: #C0C0C0;" \
                                      "}" \
                                      "QPushButton:hover {" \
                                      "background-color: #808080;" \
                                      "}"); \
                if (staff->listTables[i]->getStatus() == true) \
                button->setStyleSheet("QPushButton {background-color: #C0C0C0;color:white;}"); \
                else \
                button->setStyleSheet("QPushButton {background-color: #B8860B ; color:white;}"); \
                connect(button, &QPushButton::clicked, [=]() { \
                        menuorder *Menuorder = new menuorder(this, staff->listTables[i]); \
                        Menuorder->setAttribute(Qt::WA_DeleteOnClose); \
                        QScreen *screen = QGuiApplication::primaryScreen(); \
                        QRect geometry = screen->geometry(); \
                        int w = geometry.width(); \
                        int h = geometry.height(); \
                        Menuorder->setGeometry(0, 0, w, h); \
                        Menuorder->move(0, 0); \
                        QFont font("Arial", 13); \
                        Menuorder->setFont(font); \
                        Menuorder->show(); \
                        this->hide(); \
                }); \
        } \
    } else { \
            for (int i = 0 + row * j; i < row * (j + 1) && i < num; i++) { \
                QPushButton* button = new QPushButton(ui->centralwidget); \
                button->setGeometry(w / 2 + ((j - column / 2) * (w_table + 10)), 100 + (h_table + 10) * (i - (row * j)),w_table, h_table); \
                button->setText(QString("Table %1").arg(QString::number(i + 1))); \
                QFont font = button->font(); \
                font.setBold(true); \
                font.setPointSize(size); \
                button->setFont(font); \
                button->setStyle(QStyleFactory::create("Fusion")); \
                button->setStyleSheet("QPushButton {" \
                                      "font-weight: bold;" \
                                      "border-radius: 10px ;" \
                                      "border: 1px solid black;" \
                                      "background-color: #C0C0C0;" \
                                      "}" \
                                      "QPushButton:hover {" \
                                      "background-color: #808080;" \
                                      "}"); \
                if (staff->listTables[i]->getStatus() == true) \
                button->setStyleSheet("QPushButton {background-color: #C0C0C0;color:white;}"); \
                else \
                button->setStyleSheet("QPushButton {background-color: #B8860B ; color:white;}"); \
                connect(button, &QPushButton::clicked, [=]() { \
                        menuorder *Menuorder = new menuorder(this, staff->listTables[i]); \
                        Menuorder->setAttribute(Qt::WA_DeleteOnClose); \
                        QScreen *screen = QGuiApplication::primaryScreen(); \
                        QRect geometry = screen->geometry(); \
                        int w = geometry.width(); \
                        int h = geometry.height(); \
                        Menuorder->setGeometry(0, 0, w, h); \
                        Menuorder->move(0, 0); \
                        QFont font("Arial", 13); \
                        Menuorder->setFont(font); \
                        Menuorder->show(); \
                        this->hide(); \
                }); \
        } \
    } \
}

namespace Ui {
class employeeWindow;
}

class employeeWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit employeeWindow(Staff *newStaff, QWidget *parent = nullptr);
    ~employeeWindow();
private:
    Ui::employeeWindow *ui;
public:
    Staff* staff = new Staff;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // EMPLOYEEWINDOW_H

