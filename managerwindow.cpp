#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "QScreen"
#include <QCloseEvent>
#include "mainwindow.h"
#include "manager.h"
#include "QString"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QTextEdit"
#include <string>

ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}
void ManagerWindow::closeEvent(QCloseEvent *event){
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




