#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "managerwindow.h"
#include "QScreen"
#include "employeewindow.h"
#include "manager.h"
#include "QStyleFactory"
#include "QFont"

MainWindow::MainWindow(employeeWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->employeeWindow1 = parent;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    ui->setupUi(this);
    ui->label->setGeometry(0,0,w,h);
    ui->label->move(0,0);
    ui->pushButton->move(7*w/12, 9*h/16);

    ui->pushButton->setStyle(QStyleFactory::create("Fusion"));
    ui->pushButton->setStyleSheet("background-color: #B8860B; color: #000000; font-weight: bold;"
                                  "QPushButton {"
                                  "border-radius: 15px;" // Bo tròn viền
                                  "border: 1px solid #C6C6C6;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #00CCFF;" // Hiệu ứng nhấn
                                  "}");


    ui->employeeButton->move(9*w/12 + w/54, 9*h/16);
    ui->employeeButton->setStyle(QStyleFactory::create("Fusion"));
    ui->employeeButton->setStyleSheet("background-color: #B8860B; color: #000000; font-weight: bold;"
                                      "QPushButton {"
                                      "border-radius: 15px;" // Bo tròn viền
                                      "border: 1px solid #C6C6C6;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: #00CCFF;" // Hiệu ứng nhấn
                                      "}");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ManagerWindow* managerWindow = new ManagerWindow(this, this->employeeWindow1);
    managerWindow->setAttribute(Qt::WA_DeleteOnClose);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    managerWindow->setGeometry(0,0,w,h);
    managerWindow->move(0,0);
    managerWindow->show();
    this->hide();
}



void MainWindow::on_employeeButton_clicked()
{
    if(this->employeeWindow1 != nullptr) this->employeeWindow1->show();
    else
    {
        employeeWindow1 = new employeeWindow(new Staff, this);
        employeeWindow1->setAttribute(Qt::WA_DeleteOnClose);
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect geometry = screen->geometry();
        int w = geometry.width();
        int h = geometry.height();
        employeeWindow1->setGeometry(0,0,w,h);
        employeeWindow1->move(0,0);
        employeeWindow1->show();
    }
    this->hide();
}

