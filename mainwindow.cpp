#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "managerwindow.h"
#include "QScreen"
#include "employeewindow.h"
#include "manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    ui->setupUi(this);
    ui->label->setGeometry(0,0,w,h);
    ui->label->move(0,0);
    ui->pushButton->move(5*w/12, 9*h/16);
    ui->employeeButton->move(5*w/12, 11*h/16);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ManagerWindow* managerWindow = new ManagerWindow();
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
    employeeWindow* employeeWindow1 = new employeeWindow(new Staff, this);
    employeeWindow1->setAttribute(Qt::WA_DeleteOnClose);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    employeeWindow1->setGeometry(0,0,w,h);
    employeeWindow1->move(0,0);
    employeeWindow1->show();
    this->hide();
}

