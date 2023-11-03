#include "billwindow.h"
#include "ui_billwindow.h"
#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "ui_billwindow.h"
#include "QVBoxLayout"
#include "QPushButton"
#include "QTableWidgetItem"
#include "QHeaderView"
#include "QLabel"
#include "iostream"
#include "fstream"
#include "sstream"
#include "string"
#include "boughtitem.h"
#include "QScreen"
billwindow::billwindow(employeeWindow *parent, Table *table) :
    QMainWindow(parent),
    ui(new Ui::billwindow)
{
    this->staff = parent->staff;
    this->table = table;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();

    ui->setupUi(this);
    int cost = 200000;

    // Tạo tên của hàng và lời cảm ơn
    QLabel *logo = new QLabel();
    QLabel *thankyou = new QLabel();
    logo->setText("Group 5 's Restaurant");
    thankyou->setText("Thank you so much!!!");
    QFont font;
    font.setFamily("vivaldi");
    font.setPointSize(20);
    thankyou->setFont(font);
    logo->setFont(font);
    thankyou->setAlignment(Qt::AlignCenter);
    logo->setAlignment(Qt::AlignCenter);


  // Tạo bảng
  QTableWidget *newtable = new QTableWidget(ui->centralwidget);
  newtable->setRowCount(table->listBookedItem.size());
  newtable->setColumnCount(5);
  newtable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  newtable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  newtable->verticalHeader()->setVisible(false);
  newtable->setColumnWidth(0,0.01*w);
  newtable->setColumnWidth(1,0.15*w);
  newtable->setColumnWidth(2,0.15*w);
  newtable->setColumnWidth(3,0.04*w);
  newtable->setColumnWidth(4,0.15*w);
  //newtable->setGeometry(0,0,w,0.7*h);

  newtable->setHorizontalHeaderLabels(QStringList()<< "STT" << "Name"<<"Price"<<"Number" << "Cost");


        // Du lieu in vao bang
    QList <QString> sttarr;
    QList <QString> namearr;
    QList <QString> pricearr;
    QList <QString> quantityarr;
    QList <QString> costarr;

    QList <QTableWidgetItem *> sttWidget;
    QList <QTableWidgetItem *> nameWidget;
    QList <QTableWidgetItem *> priceWidget;
    QList <QTableWidgetItem *> quantityWidget;
    QList <QTableWidgetItem *> costWidget;

    // Tao layout va gan bang vao layout
    newtable->setFixedSize(w/2 + 10, table->listBookedItem.size()*50 + 40);
    //QWidget *layoutWidget = new QWidget();
    QVBoxLayout *horizontalLayoutWidget = new QVBoxLayout(ui->centralwidget);
    //horizontalLayoutWidget->setSizeConstraint(QLayout::SetFixedSize);
    horizontalLayoutWidget->addWidget(logo,0,Qt::AlignCenter);
    horizontalLayoutWidget->addWidget(newtable,0,Qt::AlignCenter);
    horizontalLayoutWidget->addWidget(thankyou,0,Qt::AlignCenter);
    horizontalLayoutWidget->setSpacing(20);
    horizontalLayoutWidget->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    //layoutWidget->setLayout(horizontalLayoutWidget);
    //widget->setLayout(horizontalLayoutWidget);
    //widget->setFixedSize(w/2, listBookedItem.size()*50 + 50);
    for(int i = 0;i<table->listBookedItem.size();i++)
    {
        newtable->setRowHeight(i,50);
        sttarr.append(QString::number(i + 1));
        namearr.append(table->listBookedItem[i]->getName());
        pricearr.append(table->listBookedItem[i]->getPrice());
        quantityarr.append(QString::number(table->listBookedItem[i]->getQuantity()));
        costarr.append(QString::number(table->listBookedItem[i]->getPrice().toInt() * table->listBookedItem[i]->getQuantity()));


        QTableWidgetItem *sttarr_element = new QTableWidgetItem(sttarr[i]);
        QTableWidgetItem *namearr_element = new QTableWidgetItem(namearr[i]);
        QTableWidgetItem *pricearr_element = new QTableWidgetItem(pricearr[i]);
        QTableWidgetItem *quantityarr_element = new QTableWidgetItem(quantityarr[i]);
        QTableWidgetItem *costarr_element = new QTableWidgetItem(costarr[i]);

        sttarr_element->setTextAlignment(Qt::AlignCenter);
        namearr_element->setTextAlignment(Qt::AlignCenter);
        pricearr_element->setTextAlignment(Qt::AlignCenter);
        quantityarr_element->setTextAlignment(Qt::AlignCenter);
        costarr_element->setTextAlignment(Qt::AlignCenter);

        sttWidget.append(sttarr_element);
        nameWidget.append(namearr_element);
        priceWidget.append(pricearr_element);
        quantityWidget.append(quantityarr_element);
        costWidget.append(costarr_element);

        newtable->setItem(i,0,sttWidget[i]);
        newtable->setItem(i,1,nameWidget[i]);
        newtable->setItem(i,2,priceWidget[i]);
        newtable->setItem(i,3,quantityWidget[i]);
        newtable->setItem(i,4,costWidget[i]);
    }

}

billwindow::~billwindow()
{
    delete ui;
}

void billwindow::closeEvent(QCloseEvent *event){
    event->ignore();

    // Trả lại tình trạng bàn trống cho bàn hiện tại cho vector
    for(int i = 0;i < staff->listTables.size();i++){
        if(table->getOrdinal() == staff->listTables[i]->getOrdinal())
        {
            staff->listTables[i]->setStatus(1);
            staff->listTables[i]->listBookedItem.clear();
            break;
        }
    }

    // cập nhật vào file text
    std::fstream list_table;
    list_table.open("listTable.txt", std::ios::trunc |std::ios::out);
    if(list_table.is_open() && !list_table.eof()){
        list_table.seekp(0);
        for(int i = 0;i < staff->listTables.size();i++){
            list_table << staff->listTables[i]->getOrdinal()
                       << "-"
                       << staff->listTables[i]->getStatus()
                       << std::endl;
        }
    }
    else
    {
        for(int i = 0;i < staff->listTables.size();i++){
            list_table << std::endl
                       << QString::number(staff->listTables[i]->getOrdinal()).toStdString()
                       << "-"
                       << staff->listTables[i]->getStatus();
        }
    }
    list_table.close();

    // mở window employee và cập nhật tình trạng bàn mới
    employeeWindow* employeeWindow1 = new employeeWindow(staff,this);
    employeeWindow1->setAttribute(Qt::WA_DeleteOnClose);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    employeeWindow1->setGeometry(0,0,w,h);
    employeeWindow1->move(0,0);
    employeeWindow1->show();
    this->hide();
}
