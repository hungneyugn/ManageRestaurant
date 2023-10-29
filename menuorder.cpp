#include "menuorder.h"
#include "ui_menuorder.h"
#include "billwindow.h"
#include "ui_billwindow.h"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QScreen"
#include <QTableWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "item.h"
#include <QHeaderView>
#include <vector>
#include "staff.h"
#include "mainwindow.h"

menuorder::menuorder(QWidget *parent, Table *table) :
    QMainWindow(parent),
    ui(new Ui::menuorder)
{
    qDebug () << table;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    this->table = table;
    ui->setupUi(this);

    // Them nut thanh toan
    QPushButton *payment = new QPushButton(this);
    payment->setText("Payment");
    payment->move(0.9*w, 0.875*h);

    connect(payment ,&QPushButton::clicked,[=](){
    billwindow *billwindow1 = new billwindow(this, this->table);
    billwindow1->setAttribute(Qt::WA_DeleteOnClose);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    billwindow1->setGeometry(0,0,w,h);
    billwindow1->move(0,0);
    billwindow1->show();
    this->hide();
    });

    std::fstream file("listItem.txt", std::ios::in);
    if (file.is_open()) {
        std::string line;
        QString name;
        QString price;
        QString image;
        while (!file.eof()) {
            std::getline(file, line, '\n');
            std::size_t pos1 = line.find('-');
            std::size_t pos2 = line.find('-', pos1 + 1);
            name = QString::fromStdString(line.substr(0, pos1));
            price = QString::fromStdString(line.substr(pos1 + 1, pos2 - pos1 - 1));
            image = QString::fromStdString(line.substr(pos2 + 1));
            Item newItem(name, price,image);
            newItem.setId();
            listitem.push_back(newItem);
        }
        file.close();
    }

    QTableWidget *newtable = new QTableWidget(ui->centralwidget);
    newtable->setRowCount(listitem.size());
    newtable->setColumnCount(4);
    newtable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    newtable->verticalHeader()->setFixedWidth(0.025*w);
    newtable->setColumnWidth(0,0.29*w);
    newtable->setColumnWidth(1,0.28*w);
    newtable->setColumnWidth(2,0.28*w);
    newtable->setColumnWidth(3,0.125*w);
    newtable->setGeometry(0,0,w,0.7*h);

    newtable->setHorizontalHeaderLabels(QStringList()<<"Image"<< "Name"<<"Price"<<"Number");

    QLabel *lbl_cost = new QLabel(ui->centralwidget);
    QLabel *lbl_total = new QLabel(ui->centralwidget);

    lbl_cost->setGeometry(0.875*w, 0.8*h, 0.125*w, 0.1*h);
    lbl_total->setGeometry(0.595*w, 0.8*h, 0.28*w, 0.1*h);
    lbl_cost->setAlignment(Qt::AlignCenter);
    lbl_total->setAlignment(Qt::AlignCenter);
    lbl_cost->setText("0");
    lbl_total->setText("Total");

    QList <QLabel *> imagearr;
    QList <QString> namearr;
    QList <QString> pricearr;
    QList <QTableWidgetItem *> nameWidget;
    QList <QTableWidgetItem *> priceWidget;
//    int a = table->listBookedItem.size();
//    qDebug() << a;
//    qDebug () << table->listBookedItem.size();
    for(int i = 0;i <listitem.size();i++)
    {
        QLabel *qlabel = new QLabel();
        qlabel->setPixmap(QPixmap(listitem[i].getImage()));
        qlabel->setScaledContents(true);
        imagearr.append(qlabel);
        namearr.append(listitem[i].getName());
        pricearr.append(listitem[i].getPrice());

        QTableWidgetItem *namearr_element = new QTableWidgetItem(namearr[i]);
        QTableWidgetItem *pricearr_element = new QTableWidgetItem(pricearr[i]);
        namearr_element->setTextAlignment(Qt::AlignCenter);
        pricearr_element->setTextAlignment(Qt::AlignCenter);
        nameWidget.append(namearr_element);
        priceWidget.append(pricearr_element);
        newtable->setRowHeight(i,150);

        newtable->setItem(i,1,nameWidget[i]);
        newtable->setCellWidget(i,0,imagearr[i]);
        newtable->setItem(i,2,priceWidget[i]);

        QWidget *numberLayoutWidget = new QWidget(ui->centralwidget);
        QHBoxLayout *horizontalLayoutWidget = new QHBoxLayout(numberLayoutWidget);
        QPushButton *pushButton1 = new QPushButton(numberLayoutWidget);
        pushButton1->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                                     "border-radius:50%;\n"
                                                     "height:100%;\n"
                                                     "width: 100%;\n"
                                                     "background-color: white;\n"
                                                     "border: black solid 2px;\n"
                                                     "color : Black;\n"
                                                     "font-weight: bolder;\n"
                                                     "}\n"
                                                     ""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/tru.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton1->setIcon(icon);
        pushButton1->setAutoRepeat(false);
        QLabel *numberlbl = new QLabel(numberLayoutWidget);
        if(table->listBookedItem.size() != 0)
        {
            for(int j = 0;j < table->listBookedItem.size();j++)
            {
                //int i = *(table->listBookedItem[j]->getId());
                if(listitem[i].getId() == (table->listBookedItem[j]->getId())) numberlbl->setText(QString::number(table->listBookedItem[i]->getQuantity()));
                else numberlbl->setText("0");
            }
        }
        else
        {
            numberlbl->setText("0");
        }
        QPushButton *pushButton2 = new QPushButton(numberLayoutWidget);

        pushButton2->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                                     "border-radius:50%;\n"
                                                     "height:100%;\n"
                                                     "width: 100%;\n"
                                                     "background-color: white;\n"
                                                     "border: black solid 2px;\n"
                                                     "color : Black;\n"
                                                     "font-weight: bolder;\n"
                                                     "}\n"
                                                     ""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/cong.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton2->setIcon(icon1);
        pushButton2->setAutoRepeat(false);

        horizontalLayoutWidget->addWidget(pushButton1);
        horizontalLayoutWidget->addWidget(numberlbl);
        horizontalLayoutWidget->addWidget(pushButton2);
        newtable->setCellWidget(i,3,numberLayoutWidget);


        QObject::connect(pushButton2, QPushButton::clicked, [=]() {
            lbl_cost->setText(QString::number(lbl_cost->text().toInt() + listitem[i].getPrice().toInt()));
            numberlbl->setText(QString::number(numberlbl->text().toInt() + 1));
            BoughtItem* boughtItem = nullptr;
            for (int j = 0; j < table->listBookedItem.size(); j++) {
                if (listitem[i].getId() == table->listBookedItem[j]->getId()) {
                    boughtItem = table->listBookedItem[j];
                    break;
                }
            }
            if (boughtItem == nullptr) {
                boughtItem = new BoughtItem(listitem[i].getName(), listitem[i].getId(), listitem[i].getPrice(), numberlbl->text().toInt());
                table->listBookedItem.push_back(boughtItem);
            }
//            qDebug()<<table;
            boughtItem->setQuantity(boughtItem->getQuantity());
        });

        QObject::connect(pushButton1, &QPushButton::clicked, [=]() {

            if(numberlbl->text().toInt() > 0) lbl_cost->setText(QString::number(lbl_cost->text().toInt() - listitem[i].getPrice().toInt()));
            numberlbl->setText(QString::number(numberlbl->text().toInt() == 0 ? 0 :numberlbl->text().toInt() - 1));

            for(int j = 0; j < table->listBookedItem.size();j++)
            {
                if(listitem[i].getId() == table->listBookedItem[j]->getId())
                    if(table->listBookedItem[j]->getQuantity() == 1)
                    {
                        table->listBookedItem.erase(table->listBookedItem.begin() + j);
                    }
                    else
                    {
                        table->listBookedItem[j]->setQuantity(numberlbl->text().toInt());
                    }
            }
        });
    }
}

menuorder::~menuorder()
{
    delete ui;
}

void menuorder::closeEvent(QCloseEvent *event)
{
    event->ignore();
    std::fstream list_table;
    std::fstream file;
    // ghi file listBoughtItem
    file.open("listBoughtItem.txt", std::ios::trunc |std::ios::out);
    if(file.is_open() && !file.eof()){
        file.seekp(0);
        for(int i = 0;i < table->listBookedItem.size();i++){
            file << table->listBookedItem[i]->getName().toStdString()
                 << "-"
                 << QString::number(table->listBookedItem[i]->getId()).toStdString()
                 << "-"
                 << table->listBookedItem[i]->getPrice().toStdString()
                 << "-"
                 << QString::number(table->listBookedItem[i]->getQuantity()).toStdString()
                 << std::endl;
        }

    }
    else
    {
        file.seekp(0);
        for(int i = 0;i < table->listBookedItem.size();i++){
            file << std::endl
                 << table->listBookedItem[i]->getName().toStdString()
                 << "-"
                 << QString::number(table->listBookedItem[i]->getId()).toStdString()
                 << "-"
                 << table->listBookedItem[i]->getPrice().toStdString()
                 << "-"
                 << QString::number(table->listBookedItem[i]->getQuantity()).toStdString();


        }
    }

    // load lai listtable tu file
        std::vector <Table *> updateListTable;
        std::fstream r_file("listTable.txt", std::ios::in);
        std::string line_r;
        if (r_file.is_open()) {
            while (std::getline(r_file, line_r)) {
                size_t dashPos = line_r.find("-");
                std::string ordinal_char = line_r.substr(0, dashPos);
                int ordinal = stoi(ordinal_char);

                std::string status_char = line_r.substr(dashPos + 1);
                bool status = stoi(status_char);
                Table *newtable = new Table(ordinal,status);
                updateListTable.push_back(newtable);
            }
        }

    // cap nhat lai listTable moi
        if(table->listBookedItem.size() != 0)
        {
            for(auto _table : updateListTable)
            {
                if(_table->getOrdinal() == table->getOrdinal()) _table->setStatus(0);
            }
        }

    // Luu lai listTable moi vao file text
    list_table.open("listTable.txt", std::ios::trunc |std::ios::out);
    if(list_table.is_open() && !list_table.eof()){
        list_table.seekp(0);
        for(int i = 0;i < updateListTable.size();i++){
                list_table << updateListTable[i]->getOrdinal()
                 << "-"
                 << updateListTable[i]->getStatus()
                 << std::endl;
        }

    }

    else
    {
        for(int i = 0;i < updateListTable.size();i++){
        list_table << std::endl
             << QString::number(updateListTable[i]->getOrdinal()).toStdString()
             << "-"
        << updateListTable[i]->getStatus();
        }
    }
    employeeWindow* employeeWindow1 = new employeeWindow(this);
    employeeWindow1->setAttribute(Qt::WA_DeleteOnClose);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    employeeWindow1->setGeometry(0,0,w,h);
    employeeWindow1->move(0,0);
    employeeWindow1->show();
    file.close();
    this->hide();
}
