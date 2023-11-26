#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "mainwindow.h"
#include "menuorder.h"

employeeWindow::employeeWindow(Staff *newStaff, QWidget *parent) : QMainWindow(parent),
                                                                   ui(new Ui::employeeWindow)
{
    if (newStaff->listTables.size() != 0)
        staff = newStaff;
    ui->setupUi(this);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    QLabel *img_background = new QLabel(ui->centralwidget);
    img_background->setGeometry(0, 0, w, h);
    img_background->setStyleSheet("background-image: url(:/background/table_background.png);");
    std::fstream r_file("listTable.txt", std::ios::in);
    if (staff->listTables.size() == 0)
    {
        std::string line_r;
        if (r_file.is_open())
        {
            while (std::getline(r_file, line_r))
            {
                size_t dashPos = line_r.find("-");
                std::string ordinal_char = line_r.substr(0, dashPos);
                int ordinal = stoi(ordinal_char);
                std::string status_char = line_r.substr(dashPos + 1);
                bool status = stoi(status_char);
                Table *newtable = new Table(ordinal, status);
                staff->listTables.push_back(newtable);
            }
        }
    }

    int num = staff->listTables.size();
    int size = 15;
    if (0 < num && num <= 10)
    {
        if ((num % 2) == 1)
        {
            int row = num / 2 + 1;
            int column = num / row + 1;
            MAKE_TABLE(w, h, num, row, column, size, 170, 100);
        }
        else
        {
            int row = num / 2;
            int column = num / row + 1;
            MAKE_TABLE(w, h, num, row, column, size, 170, 100);
        }
    }
    else if (10 < num && num < 41)
    {
        int row = 5;
        int column = num / row + 1;
        MAKE_TABLE(w, h, num, row, column, size, 170, 100);
    }
    else
    {
        int row = num / 10;
        if (row > 11)
        {
            row = 11;
        }
        int column = num / row + 1;
        MAKE_TABLE(w, h, num, row, column, size, 100, 50);
    }
    r_file.close();
}

employeeWindow::~employeeWindow()
{
    delete ui;
}

void employeeWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    MainWindow *mainwindow = new MainWindow(this);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    mainwindow->setGeometry(0, 0, w, h);
    mainwindow->move(0, 0);
    mainwindow->show();
    event->ignore();
}
