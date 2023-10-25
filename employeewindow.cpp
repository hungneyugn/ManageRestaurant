#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "mainwindow.h"
#include "QScreen"
#include <QCloseEvent>
#include "staff.h"
#include "table.h"
employeeWindow::employeeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employeeWindow)
{
    ui->setupUi(this);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    QTableWidget *c = new QTableWidget(ui->centralwidget);
    c->setRowCount(staff->listTables.size());
    c->setColumnCount(2);
    c->setGeometry(0, 0, w, h);
    c->setHorizontalHeaderLabels(QStringList() << "Ordinal" << "Status");
    for(int i=0; i<staff->listTables.size();i++)
    {
        QTableWidgetItem *a = new QTableWidgetItem(QString::number(staff->listTables[i].getOrdinal()));
        QTableWidgetItem *b = new QTableWidgetItem((staff->listTables[i].getStatus() == true ? "1" : "0" ));

        a->setTextAlignment(Qt::AlignCenter);
        b->setTextAlignment(Qt::AlignCenter);
        c->setItem(i, 0, a);
        c->setItem(i, 1, b);
    }

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
