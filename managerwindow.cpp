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
#include <QFileDialog>
#include <QDir>
#include "mytablewidget.h"

ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    std::fstream file("listItem.txt");
    tableItem = new QTableWidget(ui->centralwidget);
    tableItem -> setRowCount(manager->listItems.size());
    tableItem -> setColumnCount(3);
    tableItem -> setGeometry(0,0,400,400);
    tableItem -> setHorizontalHeaderLabels(QStringList() <<"Image" << "Name" << "Price");

    for (int i = 0; i < manager->listItems.size() ; i++)
    {
        QTableWidgetItem *nameTableWidget = new QTableWidgetItem(manager->listItems[i].getName());
        QTableWidgetItem *priceTableWidget = new QTableWidgetItem(manager->listItems[i].getPrice());
        nameTableWidget -> setTextAlignment(Qt::AlignCenter);
        priceTableWidget -> setTextAlignment(Qt::AlignCenter);
        tableItem -> setItem(i,1,nameTableWidget);
        tableItem -> setItem(i,2,priceTableWidget);
    };
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



void ManagerWindow::on_btnAdd_clicked()
{

    QTableWidgetItem *item = new QTableWidgetItem;

    tableItem->insertRow(tableItem->rowCount());
    int row = tableItem->rowCount();

    QPushButton *newButton = new QPushButton("newButton");
    tableItem->setCellWidget(row-1, 0, newButton);
    tableItem->setItem(row-1, 0, item);
    connect(newButton, &QPushButton::clicked, this, &ManagerWindow::openFolder);

}

void ManagerWindow::on_btnSave_clicked()
{
   int rowCount = tableItem->rowCount() - 1;
   QString name = tableItem->item(rowCount, 1)->text();
   QString price = tableItem->item(rowCount, 2)->text();
   Item newItem(name,price);
   this ->manager->listItems.push_back(newItem);
   std::fstream file;
   file.open("listItem.txt", std::ios::app);

   if(file.is_open() && file.eof()){
        file.seekg(0, std::ios::beg);
        file << name.toStdString() << "-" << price.toStdString() << std::endl;
   }
   else{
        file << std::endl << name.toStdString() << "-"<< price.toStdString();
   }
   file.close();

}


void ManagerWindow::on_btnUpload_clicked()
{

}

void ManagerWindow::openFolder(){
   QString folderPath = QFileDialog::getExistingDirectory(nullptr, "Chọn thư mục ảnh", QDir::homePath());
       if (!folderPath.isEmpty()) {
           qDebug() << "Thư mục được chọn: " << folderPath;

                       QDir directory(folderPath);

           QStringList filesAndFolders = directory.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
           for (const QString &item : filesAndFolders) {
               qDebug() << "Item: " << item;
           }
       }
}


