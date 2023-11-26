#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(employeeWindow *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    this->employeeWindow1 = parent;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    ui->setupUi(this);
    ui->label->setGeometry(0,0,w,h);
    ui->label->move(0,0);
    ui->managerButton->move(7*w/12, 9*h/16);
    ui->managerButton->setStyle(QStyleFactory::create("Fusion"));
    ui->managerButton->setStyleSheet("background-color: #B8860B; color: #000000; font-weight: bold;"
                                  "QPushButton {"
                                  "border-radius: 15px;"
                                  "border: 1px solid #C6C6C6;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #00CCFF;"
                                  "}");
    ui->employeeButton->move(9*w/12 + w/54, 9*h/16);
    ui->employeeButton->setStyle(QStyleFactory::create("Fusion"));
    ui->employeeButton->setStyleSheet("background-color: #B8860B; color: #000000; font-weight: bold;"
                                      "QPushButton {"
                                      "border-radius: 15px;"
                                      "border: 1px solid #C6C6C6;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: #00CCFF;"
                                      "}");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_managerButton_clicked()
{
    ManagerWindow* managerWindow = new ManagerWindow(this, this->employeeWindow1);
    managerWindow->setAttribute(Qt::WA_DeleteOnClose);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    managerWindow->setGeometry(0,0,w,h);
    managerWindow->move(0,0);
    managerWindow->setStyleSheet("background-color: transparent;");
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

