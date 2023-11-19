#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "QScreen"
#include <QCloseEvent>
#include "mainwindow.h"
#include "manager.h"
#include "QString"
#include "string"
#include <iostream>
#include <fstream>
#include <sstream>
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
#include "staff.h"
#include <QStyleFactory>
#include "QHeaderView"
#include "QFont"


ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)

{
    ui->setupUi(this);
    
    QFont font;
    QFont fontNoti;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();

    ui->backgroundlbl->setGeometry(0,0,w/2 - 20,h);
    ui->backgroundlbl->move(0,0);

    font.setPointSize(13); //Dat kich thuoc chu la 13
    fontNoti.setPointSize(11);
    tableItem = new QTableWidget(ui->centralwidget);
    tableItem -> setRowCount(manager->listItems.size());
    ui->centralwidget->setStyleSheet("background-color: #101010;");
    tableItem -> setColumnCount(3);

    tableItem -> setGeometry(w/2,h/10,7*w/9,7*h/10);
    tableItem->setStyleSheet(
                             "border:10px solid #101010;"
                             "color: white;"
                             );

    tableItem -> setHorizontalHeaderLabels(QStringList() <<"Image" << "Name" << "Price");
    tableItem->horizontalHeader()->setFont(font);
    //tableItem->horizontalHeader()->setStyleSheet("QHeaderView::section {border: 1px solid black; background-color: black;}");

    tableItem->setColumnWidth(0, w/9);
    tableItem->setColumnWidth(1, w/6);
    tableItem->setColumnWidth(2, w/6);

    ui->btn_add->move(w/8,7*h/12);
    ui->btn_add->setStyle(QStyleFactory::create("Fusion"));
    ui->btn_add->setStyleSheet("QPushButton {"
                               "border-radius: 10px;" // Bo tròn viền
                               "border: 1px solid black;"
                               "background-color: #C0C0C0;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: #808080;" // Hiệu ứng nhấn
                               "}");

    ui->btn_save->move(w/8,8*h/12);
    ui->btn_save->setStyle(QStyleFactory::create("Fusion"));
    ui->btn_save->setStyleSheet("QPushButton {"
                                "border-radius: 10px;" // Bo tròn viền
                                "border: 1px solid black;"
                                "background-color: #C0C0C0;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #808080;" // Hiệu ứng nhấn
                                "}");

    ui->btn_delete->move(w/4,7*h/12);
    ui->btn_delete->setStyle(QStyleFactory::create("Fusion"));
    ui->btn_delete->setStyleSheet("QPushButton {"
                                  "border-radius: 10px;" // Bo tròn viền
                                  "border: 1px solid black;"
                                  "background-color: #C0C0C0;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #808080;" // Hiệu ứng nhấn
                                  "}");

    ui->btn_update->move(w/4,2*h/3);
    ui->btn_update->setStyle(QStyleFactory::create("Fusion"));
    ui->btn_update->setStyleSheet("QPushButton {"
                                  "border-radius: 10px;" // Bo tròn viền
                                  "border: 1px solid black;"
                                  "background-color: #C0C0C0;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #808080;" // Hiệu ứng nhấn
                                  "}");
    for (int i = 0; i < manager->listItems.size() ; i++)
    {
        QTableWidgetItem *nameTableWidget = new QTableWidgetItem(manager->listItems[i].getName());
        QTableWidgetItem *priceTableWidget = new QTableWidgetItem(manager->listItems[i].getPrice());
        nameTableWidget -> setTextAlignment(Qt::AlignCenter);
        priceTableWidget -> setTextAlignment(Qt::AlignCenter);

//        nameTableWidget->setFont(font);
//        priceTableWidget->setFont(font);

        QLabel *newLabel = new QLabel();
        newLabel->setPixmap(QPixmap(manager->listItems[i].getImage()));
        newLabel->setAlignment(Qt::AlignCenter);
        newLabel->setScaledContents(true);


        tableItem->setCellWidget(i, 0 , newLabel);
        tableItem -> setItem(i,1,nameTableWidget);
        tableItem -> setItem(i,2,priceTableWidget);
        tableItem->setRowHeight(i, h/8);
        tableItem->setFont(font);
    };


    // Ẩn đường viền
//    tableItem->setShowGrid(false);

    // Ẩn tiêu đề dọc (số hàng)
    tableItem->verticalHeader()->setVisible(false);

    // Ẩn tiêu đề ngang (số cột)
    tableItem->horizontalHeader()->setVisible(false);

    QTextEdit *numtable = new QTextEdit(this);
    numtable->setGeometry(w/8,h/2,171,41);
    numtable->setFont(font);
    numtable->setStyleSheet("background-color: #C0C0C0;" "border-radius: 10px;");

    QLabel *noti = new QLabel(this);
    noti->setText("Enter the number of table");
    noti->setFont(fontNoti);
    noti->setStyleSheet("color: white;");
    noti->setGeometry(w/8,11*h/24,200,31);


    QPushButton *createtablebutton = new QPushButton(this);
    createtablebutton->setGeometry(5*w/6,h/3,171,41);
    createtablebutton->setText("Set Number Of Table");
    createtablebutton->move(w/4,h/3 + h/6);
    createtablebutton->setStyleSheet("QPushButton {"
                                    "font-weight: bold;"
                                    "border-radius: 10px;" // Bo tròn viền
                                    "border: 1px solid black;"
                                    "background-color: #C0C0C0;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #808080;" // Hiệu ứng nhấn
                                    "}"
                                    );

    int number= 0;
    std::fstream r_file("listTable.txt", std::ios::in);
    std::string line_r;
    if (r_file.is_open()) {
        while (std::getline(r_file, line_r)) {
            number++;
        }
    }
    r_file.close();
    if(number != 0)
    {
        numtable->setText(QString::number(number));
        numtable->setAlignment(Qt::AlignCenter);

    }
    // Make connect button
    connect(createtablebutton,&QPushButton::clicked,[=]()
            {
        if (numtable->toPlainText().isEmpty())
            {
            QMessageBox::warning(this,"Lỗi","Vui lòng nhập số bàn");
            }
        else
                {
               QMessageBox::information(this,"","Cập nhập số bàn thành công ");

                int num = numtable->toPlainText().toInt() ;
                std::ofstream file("listTable.txt", std::ios::trunc);
                for (int i = 0; i<num;i++)
                    {
                        file <<i+1<<"-"<<"1"<<std::endl;
                    }
                     file.close();
                }
            });
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
    if(fileName != ""){
        if (QDir(destinationPath).exists() || QDir().mkpath(destinationPath)) {
            // Thực hiện sao chép tệp
            if (QFile::copy(imagePath, destinationFilePath)) {
                qDebug() << "Sao chép thành công";
            } else {
                qDebug() << "Sao chép không thành công. Lỗi: " << sourceImage.errorString();
            }
        } else {
            qDebug() << "Không thể tạo thư mục đích hoặc thư mục đích không tồn tại.";
        }
    }else this->image_add = "";
    QIcon icon(image_add);
    newButton->setIcon(icon);
    newButton->setText("");
    newButton->setIconSize(newButton->size());
}


void ManagerWindow::on_btn_add_clicked()
{
    QFont font;
    font.setPointSize(13);

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

    tableItem->setStyleSheet(
        "QTableWidget::item {border:1px solid white; color: white;}"
        "color:white;"
        );

    tableItem->setFont(font);
    newButton = new QPushButton("upload...");
    tableItem->setCellWidget(row-1, 0, newButton);
    newButton->setStyleSheet("background-color: #101010; border: none; color: white;");
    tableItem->setRowHeight(row-1,h/8);
    image_add = "";
    connect(newButton, &QPushButton::clicked, this, &ManagerWindow::uploadImage);

}

void ManagerWindow::on_btn_save_clicked()
{
    int rowCount = tableItem->rowCount() -1;
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
        else if ((manager->listItems.size() != 0) && (manager->checkExistNameItem(name) == 0))
        {
            Item newItem(name, price, image);
            int Id = this->manager->listItems[manager->listItems.size() - 1].getId();

            newItem.setId(Id, 1);
            QString id = QString::number(newItem.getId());
            QTableWidgetItem *itemName = tableItem->item(rowCount, 1);
            QTableWidgetItem *itemPrice = tableItem->item(rowCount, 2);
            itemName->setTextAlignment(Qt::AlignCenter);
            itemPrice->setTextAlignment(Qt::AlignCenter);
            this ->manager->listItems.push_back(newItem);

            std::fstream file;
            file.open("listItem.txt", std::ios::app);
            if(file.is_open()){
                file << std::endl << id.toStdString() << "," << image.toStdString() << "," << name.toStdString() << ","<< price.toStdString();
            }
            file.close();


        }
        else if (manager->listItems.size() == 0)
        {
            Item newItem(name, price, image);
            newItem.setId(99,1);
            QString id = QString::number(newItem.getId());
            QTableWidgetItem *itemName = tableItem->item(rowCount, 1);
            QTableWidgetItem *itemPrice = tableItem->item(rowCount, 2);
            itemName->setTextAlignment(Qt::AlignCenter);
            itemPrice->setTextAlignment(Qt::AlignCenter);
            this ->manager->listItems.push_back(newItem);

            std::fstream file;
            file.open("listItem.txt", std::ios::app);
            file << id.toStdString() << "," << image.toStdString() << "," << name.toStdString() << "," << price.toStdString();
            file.close();


        }
        else if(manager->checkExistNameItem(name) == 1)
        {
             QMessageBox::critical(this, "Lỗi", "Tên món ăn đã tồn tại");
        }
    }
}


void ManagerWindow::on_btn_delete_clicked()
{
    bool isItemSelected = tableItem->selectionModel()->hasSelection();
    int row = this->tableItem->currentRow();
    QItemSelectionModel *selectionModel = tableItem->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();
    if (selectedRows.size() > 1) {
        QMessageBox::information(this, "Thông báo lỗi", "Bạn đã chọn nhiều hơn một hàng, vui lòng chọn lại bạn nhé !!!");
    }
    else if (row >= 0 && isItemSelected == true) {
        this->tableItem->removeRow(row);
        manager->listItems.erase(manager->listItems.begin() + row);
        std::fstream file;
        file.open("listItem.txt", std::ios::trunc |std::ios::out);
        if(file.is_open()){
            file.seekp(0, std::ios::end);
            for(int i = 0;i < manager->listItems.size(); i++){
                if (file.tellp() == 0) {
                    // Nếu tệp trống, ghi dữ liệu mà không có dòng trống ở đầu
                    file << manager->listItems[i].getId() << "," <<  manager->listItems[i].getImage().toStdString() << "," << manager->listItems[i].getName().toStdString() << "," << manager->listItems[i].getPrice().toStdString();

                } else {
                    // Nếu không trống, di chuyển con trỏ ghi đến đầu và ghi dữ liệu
                    file << std::endl << manager->listItems[i].getId() << "," << manager->listItems[i].getImage().toStdString() << "," << manager->listItems[i].getName().toStdString() << ","<< manager->listItems[i].getPrice().toStdString();
                }
            }
        }
        file.close();
    }
    else
    {
        if (!isItemSelected) {
        QMessageBox::information(this, "Thông báo lỗi", "Bạn phải chọn hàng trước khi xóa!");
    }
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
                        file << manager->listItems[i].getId() << "," <<  manager->listItems[i].getImage().toStdString() << "," << manager->listItems[i].getName().toStdString() << "," << manager->listItems[i].getPrice().toStdString();

                    } else {
                        // Nếu không trống, di chuyển con trỏ ghi đến đầu và ghi dữ liệu
                        file << std::endl << manager->listItems[i].getId() << "," << manager->listItems[i].getImage().toStdString() << "," << manager->listItems[i].getName().toStdString() << ","<< manager->listItems[i].getPrice().toStdString();
                    }
                }
        }
        file.close();
        QMessageBox::information(this, "Update", "Update successfully.");
    }
}
else {
    QMessageBox::information(this, "Update error", "Please enter and save data before updating.");

    }
}



