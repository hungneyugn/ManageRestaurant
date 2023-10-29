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


ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
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
    QTableWidgetItem *item = new QTableWidgetItem;

    tableItem->insertRow(tableItem->rowCount());
    int row = tableItem->rowCount();

    QPushButton *newButton = new QPushButton("upload...");
    tableItem->setCellWidget(row-1, 0, newButton);
    tableItem->setItem(row-1, 0, item);
    newButton->setStyleSheet("background: rgba(0, 0, 0, 0); border: none;");

    connect(newButton, &QPushButton::clicked, this, &ManagerWindow::uploadImage);

}


void ManagerWindow::on_btn_save_clicked()
{
    int rowCount = tableItem->rowCount() - 1;
    QString name = tableItem->item(rowCount, 1)->text();
    QString price = tableItem->item(rowCount, 2)->text();
    QString image = image_add;
    Item newItem(name,price, image);
    this ->manager->listItems.push_back(newItem);
    std::fstream file;
    file.open("listItem.txt", std::ios::app);
    file.seekp(0, std::ios::end);

    if(file.is_open()){
        file.seekp(0, std::ios::end);
        if (file.tellp() == 0) {
            // Nếu tệp trống, ghi dữ liệu mà không có dòng trống ở đầu
            file << image.toStdString() << "," << name.toStdString() << "," << price.toStdString() << std::endl;
        } else {
            // Nếu không trống, di chuyển con trỏ ghi đến đầu và ghi dữ liệu
            file << image.toStdString() << "," << name.toStdString() << ","<< price.toStdString();
        }
    }

    file.close();
}

