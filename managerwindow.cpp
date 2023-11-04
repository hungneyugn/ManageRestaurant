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
#include "QIcon"
#include "QLabel"
#include "QPixmap"
#include <cmath>
#include "QScreen"
#include "QMessageBox"


ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    tableItem = new QTableWidget(ui->centralwidget);
    tableItem -> setRowCount(manager->listItems.size());
    tableItem -> setColumnCount(3);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    tableItem -> setGeometry(0,0,7*w/9,h);
    tableItem -> setHorizontalHeaderLabels(QStringList() <<"Image" << "Name" << "Price");
    tableItem->setColumnWidth(0, 7*w/27);
    tableItem->setColumnWidth(1, 7*w/27);
    tableItem->setColumnWidth(2, 7*w/27);

    ui->btn_add->move(5*w/6,h/2);
    ui->btn_save->move(5*w/6,7*h/12);
    ui->btn_delete->move(5*w/6,2*h/3);
    ui->btn_update->move(5*w/6,3*h/4);
    for (int i = 0; i < manager->listItems.size() ; i++)
    {
        QTableWidgetItem *nameTableWidget = new QTableWidgetItem(manager->listItems[i].getName());
        QTableWidgetItem *priceTableWidget = new QTableWidgetItem(manager->listItems[i].getPrice());
        nameTableWidget -> setTextAlignment(Qt::AlignCenter);
        priceTableWidget -> setTextAlignment(Qt::AlignCenter);

        QLabel *newLabel = new QLabel();
        newLabel->setPixmap(QPixmap(manager->listItems[i].getImage()));
        newLabel->setAlignment(Qt::AlignCenter);

        tableItem->setCellWidget(i, 0 , newLabel);
        tableItem -> setItem(i,1,nameTableWidget);
        tableItem -> setItem(i,2,priceTableWidget);
        tableItem->setRowHeight(i, h/5);
    };
}
ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::closeEvent(QCloseEvent *event){
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


void ManagerWindow::uploadImage()
{
    QString destinationFolderName = "image"; // Tên thư mục đích
    QString imagePath = QFileDialog::getOpenFileName(this, "Chọn hình ảnh", QDir::homePath(), "Ảnh (*.png *.jpg *.jpeg)");

    QFile sourceImage(imagePath);
    QString fileName = QFileInfo(imagePath).fileName(); // Lấy tên tệp của hình ảnh

    // Lấy đường dẫn thư mục hiện tại của ứng dụng
    QString currentPath = QDir::currentPath();

    // Tạo đường dẫn đầy đủ đến thư mục đích
    QString destinationPath = currentPath + "/" + destinationFolderName;
    QString destinationFilePath = destinationPath + "/" + fileName; // Đường dẫn đầy đủ đến tệp mới
    this->image_add = destinationFilePath;
    if (QDir(destinationPath).exists() || QDir().mkpath(destinationPath)) {
        // Thực hiện sao chép tệp
        if (QFile::copy(imagePath, destinationFilePath)) {
            qDebug() << "Sao chép thành công";
            qDebug() << destinationFilePath;
        } else {
            qDebug() << "Sao chép không thành công. Lỗi: " << sourceImage.errorString();
        }
    } else {
        qDebug() << "Không thể tạo thư mục đích hoặc thư mục đích không tồn tại.";
    }
}


void ManagerWindow::on_btn_add_clicked()
{
    QString str = "";
    QTableWidgetItem *item1 = new QTableWidgetItem(str);
    QTableWidgetItem *item2 = new QTableWidgetItem(str);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int h = geometry.height();
    tableItem->insertRow(tableItem->rowCount());
    int row = tableItem->rowCount();
    tableItem->setItem(row - 1, 1, item1);
    tableItem->setItem(row - 1, 2, item2);

    newButton = new QPushButton("upload...");
    tableItem->setCellWidget(row-1, 0, newButton);
    newButton->setStyleSheet("background: rgba(0, 0, 0, 0); border: none;");
    tableItem->setRowHeight(row-1,h/5);
    image_add = "";
    connect(newButton, &QPushButton::clicked, this, &ManagerWindow::uploadImage);

}


void ManagerWindow::on_btn_save_clicked()
{
    int rowCount = tableItem->rowCount() - 1;

    if (tableItem->rowCount() == 0)
    {
        QMessageBox::critical(this, "Lỗi", "Vui lòng nhập thông tin.");
    }
    else
    {
        QString name = tableItem->item(rowCount, 1)->text();
        QString price = tableItem->item(rowCount, 2)->text();
        QString image = image_add;

        if (name.isEmpty() || price.isEmpty() || image.isEmpty()) QMessageBox::critical(this, "Lỗi", "Vui lòng nhập thông tin.");
        else if ((manager->listItems.size() != 0) && name != manager->listItems[rowCount].getName())
        {
            Item newItem(name, price, image);

            QTableWidgetItem *itemName = tableItem->item(rowCount, 1);
            QTableWidgetItem *itemPrice = tableItem->item(rowCount, 2);
            itemName->setTextAlignment(Qt::AlignCenter);
            itemPrice->setTextAlignment(Qt::AlignCenter);
            this ->manager->listItems.push_back(newItem);

            std::fstream file;
            file.open("listItem.txt", std::ios::app);
            if(file.is_open()){
                file << std::endl << image.toStdString() << "," << name.toStdString() << ","<< price.toStdString();
            }
            file.close();

            QIcon icon(image_add);
            newButton->setIcon(icon);
            newButton->setText("");
            newButton->setIconSize(newButton->size());
        }
        else if (manager->listItems.size() == 0)
        {
            Item newItem(name, price, image);

            QTableWidgetItem *itemName = tableItem->item(rowCount, 1);
            QTableWidgetItem *itemPrice = tableItem->item(rowCount, 2);
            itemName->setTextAlignment(Qt::AlignCenter);
            itemPrice->setTextAlignment(Qt::AlignCenter);
            this ->manager->listItems.push_back(newItem);

            std::fstream file;
            file.open("listItem.txt", std::ios::app);
            file << image.toStdString() << "," << name.toStdString() << "," << price.toStdString();
            file.close();

            QIcon icon(image_add);
            newButton->setIcon(icon);
            newButton->setText("");
            newButton->setIconSize(newButton->size());
        }
    }
}


void ManagerWindow::on_btn_delete_clicked()
{
    int row = this->tableItem->currentRow();
    if (row >= 0) {
        this->tableItem->removeRow(row);
        manager->listItems.erase(manager->listItems.begin() + row);
        std::fstream file;
        file.open("listItem.txt", std::ios::trunc |std::ios::out);
        if(file.is_open()){
            file.seekp(0, std::ios::end);
            for(int i = 0;i < manager->listItems.size(); i++){
                if (file.tellp() == 0) {
                    // Nếu tệp trống, ghi dữ liệu mà không có dòng trống ở đầu
                    file <<  manager->listItems[i].getImage().toStdString() << "," << manager->listItems[i].getName().toStdString() << "," << manager->listItems[i].getPrice().toStdString();

                } else {
                    // Nếu không trống, di chuyển con trỏ ghi đến đầu và ghi dữ liệu
                    file << std::endl << manager->listItems[i].getImage().toStdString() << "," << manager->listItems[i].getName().toStdString() << ","<< manager->listItems[i].getPrice().toStdString();
                }
            }
        }
        file.close();
    }
}


void ManagerWindow::on_btn_update_clicked()
{
    int row = this->tableItem->currentRow();
    if (row >= 0 && row < manager->listItems.size()) {
            QString name = tableItem->item(row, 1)->text();
            QString price = tableItem->item(row, 2)->text();
            QString image = image_add;

            QString nameOld = manager->listItems[row].getName();
            QString priceOld = manager->listItems[row].getPrice();

            if (nameOld == name && priceOld == price) {
            QMessageBox::information(this, "There's nothing to update", "You have not edited the data. Please correct data before updating.");
            return;
            }
            else{

                manager->listItems[row].setName(name);
                manager->listItems[row].setPrice(price);
                manager->listItems[row].setImage(image);

                std::fstream file;
                file.open("listItem.txt", std::ios::trunc |std::ios::out);
                if(file.is_open()){
                    file.seekp(0, std::ios::end);
                    for(int i = 0;i < manager->listItems.size(); i++){
                        if (file.tellp() == 0) {
                            // Nếu tệp trống, ghi dữ liệu mà không có dòng trống ở đầu
                            file <<  manager->listItems[i].getImage().toStdString() << "," << manager->listItems[i].getName().toStdString() << "," << manager->listItems[i].getPrice().toStdString();

                        } else {
                            // Nếu không trống, di chuyển con trỏ ghi đến đầu và ghi dữ liệu
                            file << std::endl << manager->listItems[i].getImage().toStdString() << "," << manager->listItems[i].getName().toStdString() << ","<< manager->listItems[i].getPrice().toStdString();
                        }
                    }
                }
                file.close();
            }
    }
    else {
            QMessageBox::information(this, "Update error", "Please enter and save data before updating.");

    }
}

