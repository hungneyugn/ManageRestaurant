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
    QTableWidget *tableItem = new QTableWidget(ui->centralwidget);
    tableItem -> setRowCount(manager->listItems.size());
    tableItem -> setColumnCount(3);
    tableItem -> setGeometry(0,0,800,800);
    tableItem -> setHorizontalHeaderLabels(QStringList() << "Image" << "Name" << "Price");

    float size =800/3;
    tableItem->setColumnWidth(0, size);
    tableItem->setColumnWidth(1, size);
    tableItem->setColumnWidth(2, size);

    for (int i = 0; i < manager->listItems.size() ; i++)
    {
        QTableWidgetItem *nameTableWidget = new QTableWidgetItem(manager->listItems[i].getName());
        QTableWidgetItem *priceTableWidget = new QTableWidgetItem(manager->listItems[i].getPrice());
        nameTableWidget -> setTextAlignment(Qt::AlignCenter);
        priceTableWidget -> setTextAlignment(Qt::AlignCenter);
        tableItem -> setItem(i,1,nameTableWidget);
        tableItem -> setItem(i,2,priceTableWidget);
        tableItem->setRowHeight(i, 50);
    }
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




