#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "QScreen"
#include <QCloseEvent>
#include "mainwindow.h"
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
void ManagerWindow::closeEvent(){
    this->hide();
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    MainWindow b;
    b.setGeometry(0,0,w,h);
    b.move(0,0);
    b.show();
}
