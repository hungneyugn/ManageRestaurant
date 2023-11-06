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

employeeWindow::employeeWindow(Staff *newStaff, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employeeWindow)
{
    if(newStaff->listTables.size()!= 0) staff = newStaff;
    ui->setupUi(this);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();

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

    int num = staff->listTables.size();
    if (0<num && num <=10){
        if ((num - num/2*2) == 1){
            int row = num/2+1;
            int column = num/row +1 ;
            for (int j = 0; j < column;j++)
            {
                if (j < column/2){
                    for (int i = 0+row*j; i < row*(j+1) && i<num; i++) {
                        QPushButton* button = new QPushButton(ui->centralwidget);
                        button->setGeometry(w/2+((j-column/2)*205),100+ i * 100 - 100*(row*j),200,100);
                        button->setText(QString("Table %1").arg(QString::number(i + 1)));
                        if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton { background-color: green }");
                        else button->setStyleSheet("QPushButton { background-color: red }");
                        connect(button,&QPushButton::clicked,[=]()
                                {
                                    menuorder *Menuorder = new menuorder(this, staff->listTables[i]);
                                    Menuorder->setAttribute(Qt::WA_DeleteOnClose);

                                    QScreen *screen = QGuiApplication::primaryScreen();
                                    QRect geometry = screen->geometry();
                                    int w = geometry.width();
                                    int h = geometry.height();
                                    Menuorder->setGeometry(0,0,w,h);
                                    Menuorder->move(0,0);
                                    QFont font("Arial", 13);
                                    Menuorder->setFont(font);
                                    Menuorder->show();
                                    this->hide();
                                });
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
                                    menuorder *Menuorder = new menuorder(this, staff->listTables[i]);
                                    Menuorder->setAttribute(Qt::WA_DeleteOnClose);

                                    QScreen *screen = QGuiApplication::primaryScreen();
                                    QRect geometry = screen->geometry();
                                    int w = geometry.width();
                                    int h = geometry.height();
                                    Menuorder->setGeometry(0,0,w,h);
                                    Menuorder->move(0,0);
                                    QFont font("Arial", 13);
                                    Menuorder->setFont(font);
                                    Menuorder->show();
                                    this->hide();
                                });

                    }
                }
            }
        }
        else
        {
            int row = num/2;
            int column = num/row +1 ;
            for (int j = 0; j < column;j++)
            {
                if (j < column/2){
                    for (int i = 0+row*j; i < row*(j+1) && i<num; i++) {
                        QPushButton* button = new QPushButton(ui->centralwidget);
                        button->setGeometry(w/2+((j-column/2)*205),100+ i * 100 - 100*(row*j),200,100);
                        button->setText(QString("Table %1").arg(QString::number(i + 1)));
                        if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton { background-color: green }");
                        else button->setStyleSheet("QPushButton { background-color: red }");
                        connect(button,&QPushButton::clicked,[=]()
                                {
                                    menuorder *Menuorder = new menuorder(this, staff->listTables[i]);
                                    Menuorder->setAttribute(Qt::WA_DeleteOnClose);

                                    QScreen *screen = QGuiApplication::primaryScreen();
                                    QRect geometry = screen->geometry();
                                    int w = geometry.width();
                                    int h = geometry.height();
                                    Menuorder->setGeometry(0,0,w,h);
                                    Menuorder->move(0,0);
                                    QFont font("Arial", 13);
                                    Menuorder->setFont(font);
                                    Menuorder->show();
                                    this->hide();
                                });

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
                                    menuorder *Menuorder = new menuorder(this, staff->listTables[i]);
                                    Menuorder->setAttribute(Qt::WA_DeleteOnClose);

                                    QScreen *screen = QGuiApplication::primaryScreen();
                                    QRect geometry = screen->geometry();
                                    int w = geometry.width();
                                    int h = geometry.height();
                                    Menuorder->setGeometry(0,0,w,h);
                                    Menuorder->move(0,0);
                                    QFont font("Arial", 13);
                                    Menuorder->setFont(font);
                                    Menuorder->show();
                                    this->hide();
                                });

                    }
                }
            }
        }
    }
    else if (10 <num && num < 41)
    {
        int row = 5 ;
        int column = num/row +1 ;
        for (int j = 0; j < column;j++)
        {
            if (j < column/2){
                for (int i = 0+row*j; i < row*(j+1) && i<num; i++) {
                    QPushButton* button = new QPushButton(ui->centralwidget);
                    button->setGeometry(w/2+((j-column/2)*205),100+ i * 100 - 100*(row*j),200,100);
                    button->setText(QString("Table %1").arg(QString::number(i + 1)));
                    if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton { background-color: green }");
                    else button->setStyleSheet("QPushButton { background-color: red }");
                    connect(button,&QPushButton::clicked,[=]()
                            {
                                menuorder *Menuorder = new menuorder(this, staff->listTables[i]);
                                Menuorder->setAttribute(Qt::WA_DeleteOnClose);

                                QScreen *screen = QGuiApplication::primaryScreen();
                                QRect geometry = screen->geometry();
                                int w = geometry.width();
                                int h = geometry.height();
                                Menuorder->setGeometry(0,0,w,h);
                                Menuorder->move(0,0);
                                QFont font("Arial", 13);
                                Menuorder->setFont(font);
                                Menuorder->show();
                                this->hide();
                            });
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
                                menuorder *Menuorder = new menuorder(this, staff->listTables[i]);
                                Menuorder->setAttribute(Qt::WA_DeleteOnClose);

                                QScreen *screen = QGuiApplication::primaryScreen();
                                QRect geometry = screen->geometry();
                                int w = geometry.width();
                                int h = geometry.height();
                                Menuorder->setGeometry(0,0,w,h);
                                Menuorder->move(0,0);
                                QFont font("Arial", 13);
                                Menuorder->setFont(font);
                                Menuorder->show();
                                this->hide();
                            });
                }
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
