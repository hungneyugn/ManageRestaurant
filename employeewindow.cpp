#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "mainwindow.h"
#include "menuorder.h"
#include <QStyleFactory>


employeeWindow::employeeWindow(Staff *newStaff, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employeeWindow)
{
    if(newStaff->listTables.size()!= 0) staff = newStaff;
    ui->setupUi(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    QLabel* img_background = new QLabel(ui->centralwidget);
    img_background->setGeometry(0,0,w,h);
    img_background->setStyleSheet("background-image: url(:/background/table_background.png);");
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
    int size = 20;
    if (0<num && num <=10){
        if ((num - num/2*2) == 1){
            int row = num/2+1;
            int column = num/row +1 ;
            for (int j = 0; j < column;j++)
            {
                if (j < column/2){
                    for (int i = 0+row*j; i < row*(j+1) && i<num; i++) {
                        QPushButton* button = new QPushButton(ui->centralwidget);
                        button->setGeometry(w/2+((j-column/2)*210),200+ i * 110 - 110*(row*j),200,100);
                        button->setText(QString("Table %1").arg(QString::number(i + 1)));
                        QFont font = button->font();
                        font.setBold(true);
                        font.setPointSize(size);
                        button->setFont(font);
                        button->setStyle(QStyleFactory::create("Fusion"));
                        button->setStyleSheet("QPushButton {"
                                              "font-weight: bold;"
                                              "border-radius: 10px ;" // Bo tròn viền
                                              "border: 1px solid black;"
                                              "background-color: #C0C0C0;"
                                              "}"
                                              "QPushButton:hover {"
                                              "background-color: #808080;" // Hiệu ứng nhấn
                                              "}"
                                              );
                        if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton {background-color: #C0C0C0;color:white;}");
                        else button->setStyleSheet("QPushButton {background-color: #B8860B ; color:white;}");
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
                        button->setGeometry(w/2+((j-column/2)*210),200+ i * 110 - 110*(row*j),200,100);
                        button->setText(QString("Table %1").arg(QString::number(i + 1)));
                        QFont font = button->font();
                        font.setBold(true);
                        font.setPointSize(size);
                        button->setFont(font);
                        button->setStyle(QStyleFactory::create("Fusion"));
                        button->setStyleSheet("QPushButton {"
                                              "font-weight: bold;"
                                              "border-radius: 10px ;" // Bo tròn viền
                                              "border: 1px solid black;"
                                              "background-color: #C0C0C0;"
                                              "background-image: url(:/C:/Users/BRAVO/Downloads/table1.png);"
                                              "}"
                                              "QPushButton:hover {"
                                              "background-color: #808080;" // Hiệu ứng nhấn
                                              "}"
                                              );
                        if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton {background-color: #C0C0C0;color:white;}");
                        else button->setStyleSheet("QPushButton {background-color: #B8860B ; color:white;}");
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
                        button->setGeometry(w/2+((j-column/2)*210),200+ i * 110 - 110*(row*j),200,100);
                        button->setText(QString("Table %1").arg(QString::number(i + 1)));
                        QFont font = button->font();
                        font.setBold(true);
                        font.setPointSize(size);
                        button->setFont(font);
                        button->setStyle(QStyleFactory::create("Fusion"));
                        button->setStyleSheet("QPushButton {"
                                              "font-weight: bold;"
                                              "border-radius: 10px ;" // Bo tròn viền
                                              "border: 1px solid black;"
                                              "background-color: #C0C0C0;"
                                              "background-image: url(:/C:/Users/BRAVO/Downloads/table1.png);"
                                              "}"
                                              "QPushButton:hover {"
                                              "background-color: #808080;" // Hiệu ứng nhấn
                                              "}"
                                              );
                        if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton {background-color: #C0C0C0;color:white;}");
                        else button->setStyleSheet("QPushButton {background-color: #B8860B ; color:white;}");
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
                        button->setGeometry(w/2+((j-column/2)*210),200+ i * 110 - 110*(row*j),200,100);
                        button->setText(QString("Table %1").arg(QString::number(i + 1)));
                        QFont font = button->font();
                        font.setBold(true);
                        font.setPointSize(size);
                        button->setFont(font);
                        button->setStyle(QStyleFactory::create("Fusion"));
                        button->setStyleSheet("QPushButton {"
                                              "font-weight: bold;"
                                              "border-radius: 10px ;" // Bo tròn viền
                                              "border: 1px solid black;"
                                              "background-color: #C0C0C0;"
                                              "}"
                                              "QPushButton:hover {"
                                              "background-color: #808080;" // Hiệu ứng nhấn
                                              "}"
                                              );
                        if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton {background-color: #C0C0C0;color:white;}");
                        else button->setStyleSheet("QPushButton {background-color: #B8860B ; color:white;}");
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
                    button->setGeometry(w/2+((j-column/2)*210),200+ i * 110 - 110*(row*j),200,100);
                    button->setText(QString("Table %1").arg(QString::number(i + 1)));
                    QFont font = button->font();
                    font.setBold(true);
                    font.setPointSize(size);
                    button->setFont(font);
                    button->setStyle(QStyleFactory::create("Fusion"));
                    button->setStyleSheet("QPushButton {"
                                          "font-weight: bold;"
                                          "border-radius: 10px ;" // Bo tròn viền
                                          "border: 1px solid black;"
                                          "background-color: #C0C0C0;"
                                          "}"
                                          "QPushButton:hover {"
                                          "background-color: #808080;" // Hiệu ứng nhấn
                                          "}"
                                          );
                    if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton {background-color: #C0C0C0;color:white;}");
                    else button->setStyleSheet("QPushButton {background-color: #B8860B ; color:white;}");
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
                    button->setGeometry(w/2+((j-column/2)*210),200+ i * 110 - 110*(row*j),200,100);
                    button->setText(QString("Table %1").arg(QString::number(i + 1)));
                    QFont font = button->font();
                    font.setBold(true);
                    font.setPointSize(size);
                    button->setFont(font);
                    button->setStyle(QStyleFactory::create("Fusion"));
                    button->setStyleSheet("QPushButton {"
                                          "font-weight: bold;"
                                          "border-radius: 10px ;" // Bo tròn viền
                                          "border: 1px solid black;"
                                          "background-color: #C0C0C0;"
                                          "}"
                                          "QPushButton:hover {"
                                          "background-color: #808080;" // Hiệu ứng nhấn
                                          "}"
                                          );
                    if(staff->listTables[i]->getStatus() == true) button->setStyleSheet("QPushButton {background-color: #C0C0C0;color:white;}");
                    else button->setStyleSheet("QPushButton {background-color: #B8860B ; color:white;}");
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
