#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "mainwindow.h"
#include "QScreen"
#include <QCloseEvent>
employeeWindow::employeeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employeeWindow)
{
    ui->setupUi(this);
}

employeeWindow::~employeeWindow()
{
    delete ui;
}

void employeeWindow::closeEvent(QCloseEvent *event){
    event->ignore();
    MainWindow *mainwindow = new MainWindow();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    mainwindow->setGeometry(0,0,w,h);
    mainwindow->move(0,0);
    mainwindow->show();
    this->hide();
}
