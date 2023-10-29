#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "mainwindow.h"
#include "QScreen"
#include <QCloseEvent>
#include "staff.h"
#include "table.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"
#include "menuorder.h"
#include <QPushButton>

employeeWindow::employeeWindow(QWidget *parent,Table *table ) :
    QMainWindow(parent),
    ui(new Ui::employeeWindow)
{
//    qDebug() << table->listBookedItem.size();
    ui->setupUi(this);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    //    QTableWidget *c = new QTableWidget(ui->centralwidget);
    //    c->setRowCount(staff->listTables.size());
    //    c->setColumnCount(2);
    //    c->setGeometry(0, 0, w, h);
    //    c->setHorizontalHeaderLabels(QStringList() << "Ordinal" << "Status");
    //    for(int i=0; i<staff->listTables.size();i++)
    //    {
    //        QTableWidgetItem *a = new QTableWidgetItem(QString::number(staff->listTables[i].getOrdinal()));
    //        QTableWidgetItem *b = new QTableWidgetItem((staff->listTables[i].getStatus() == true ? "1" : "0" ));

    //        a->setTextAlignment(Qt::AlignCenter);
    //        b->setTextAlignment(Qt::AlignCenter);
    //        c->setItem(i, 0, a);
    //        c->setItem(i, 1, b);
    //    }
    std::fstream r_file("listTable.txt", std::ios::in);
    if(staff->listTables.size() == 0)
    {
        std::string line_r;
        if (r_file.is_open()) {
            while (std::getline(r_file, line_r)) {
                size_t dashPos = line_r.find("-");
                std::string ordinal_char = line_r.substr(0, dashPos);
                int ordinal = stoi(ordinal_char);

                std::string status_char = line_r.substr(dashPos + 1);
                bool status = stoi(status_char);
                Table *newtable = new Table(ordinal,status);
                staff->listTables.push_back(newtable);
            }
        }
    }
    else
    {
        for (auto list : staff->listTables)
        {
            if(list->getOrdinal() == table->getOrdinal()) list->setStatus(table->getStatus());
        }
    }


    int num = staff->listTables.size();
    int row = num/2 + 1;
    int column = num/5 +1 ;
    for (int j = 0; j < column;j++)
    {
        if (j < column/2){
            for (int i = 0+row*j; i < row*(j+1) && i<num; i++)
            {
                QPushButton* button = new QPushButton(ui->centralwidget);
                button->setGeometry(w/2-((column/2-j)*205),100+ i * 100 - 100*(row*j),200,100);
                button->setText(QString("Table %1").arg(QString::number(i + 1)));
                if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton { background-color: green }");
                else button->setStyleSheet("QPushButton { background-color: red }");
                connect(button,&QPushButton::clicked,[this]()
                        {
//                    QScreen *screen = QGuiApplication::primaryScreen();
//                    QRect geometry = screen->geometry();
//                    int w = geometry.width();
//                    int h = geometry.height();
//                    ui->setupUi(this);
//                    this->setGeometry(0,0,w,h);
//                    this->move(0,0);

//                    menuorder *Menuorder = new menuorder();
//                    Menuorder->setAttribute(Qt::WA_DeleteOnClose);
//                    Menuorder->show();
                        } );
            }
        }
        else
        {
            for (int i = 0+row*j; i < row*(j+1) && i<num; i++) {

                QPushButton* button = new QPushButton(ui->centralwidget);
                button->setGeometry(w/2+((j-column/2)*205),100+ i * 100 - 100*(row*j),200,100);
                button->setText(QString("Table %1").arg(QString::number(i + 1)));
                if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton { background-color: green }");
                else button->setStyleSheet("QPushButton { background-color: red }");
                connect(button,&QPushButton::clicked,[=]()
                        {
//                    QScreen *screen = QGuiApplication::primaryScreen();
//                    QRect geometry = screen->geometry();
//                    int w = geometry.width();
//                    int h = geometry.height();
//                    ui->setupUi(this);
//                    this->setGeometry(0,0,w,h);
//                    this->move(0,0);
                     qDebug()<< staff->listTables[i];
                    menuorder *Menuorder = new menuorder(this, staff->listTables[i]);
                    Menuorder->setAttribute(Qt::WA_DeleteOnClose);

                    QScreen *screen = QGuiApplication::primaryScreen();
                    QRect geometry = screen->geometry();
                    int w = geometry.width();
                    int h = geometry.height();
                    Menuorder->setGeometry(0,0,w,h);
                    Menuorder->move(0,0);

                    Menuorder->show();
                    this->hide();
                        } );
            }
        }
    }
    r_file.close();
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
