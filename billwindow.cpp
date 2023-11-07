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

    ui->setupUi(this);

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

    // Tạo hàng tính tổng số tiền

    // Tạo layout chứa hàng tổng tiền
    QWidget *totalLayoutWidget = new QWidget();
    totalLayoutWidget->setFixedSize(w/2, 50);
    QHBoxLayout *totalLayout = new QHBoxLayout(totalLayoutWidget);

    // Tạo label chữ total và label tổng tiền
    QLabel *lbl_cost = new QLabel(totalLayoutWidget);
    QLabel *lbl_cost_value = new QLabel(totalLayoutWidget);
    lbl_cost->setText("Total");

    // Từ các món ăn đã mua mà tính tổng tiền
    double total_cost = 0;
    for(int i = 0; i<table->listBookedItem.size();i++)
    {
        total_cost += table->listBookedItem[i]->getPrice().toInt()*table->listBookedItem[i]->getQuantity();
    }
    lbl_cost_value->setText(QString::number(total_cost));

    // Gán 2 label vào QHBoxLayout
    totalLayout->addWidget(lbl_cost);
    totalLayout->addWidget(lbl_cost_value);
    totalLayout->setAlignment(lbl_cost, Qt::AlignLeft);
    totalLayout->setAlignment(lbl_cost_value, Qt::AlignRight);

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

  newtable->setHorizontalHeaderLabels(QStringList()<< "STT" << "Name"<<"Price"<<"Number" << "Cost");
  newtable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: 1px solid black; background-color: rgba(201, 201, 201, 0.5);}");


    // Du lieu in vao bang
    QList <QString> ordinalarr;
    QList <QString> namearr;
    QList <QString> pricearr;
    QList <QString> quantityarr;
    QList <QString> costarr;

    QList <QTableWidgetItem *> ordinalWidget;
    QList <QTableWidgetItem *> nameWidget;
    QList <QTableWidgetItem *> priceWidget;
    QList <QTableWidgetItem *> quantityWidget;
    QList <QTableWidgetItem *> costWidget;

    // Tao layout va gan bang vao layout
    newtable->setFixedSize(w/2 + 10, table->listBookedItem.size()*50 + 20);
    //QWidget *layoutWidget = new QWidget();
    QVBoxLayout *horizontalLayoutWidget = new QVBoxLayout(ui->centralwidget);
    //horizontalLayoutWidget->setSizeConstraint(QLayout::SetFixedSize);

    // Hàng logo
    horizontalLayoutWidget->addWidget(logo,0,Qt::AlignCenter);

    // Hàng bảng tính tiền
    horizontalLayoutWidget->addWidget(newtable,0,Qt::AlignCenter);

    // Hàng tính tổng cộng tiền
    horizontalLayoutWidget->addWidget(totalLayoutWidget,0,Qt::AlignCenter);

    // Hàng dòng cảm ơn
    horizontalLayoutWidget->addWidget(thankyou,0,Qt::AlignCenter);
    horizontalLayoutWidget->setSpacing(5);
    horizontalLayoutWidget->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    for(int i = 0;i<table->listBookedItem.size();i++)
    {
        newtable->setRowHeight(i,50);
        ordinalarr.append(QString::number(i + 1));
        namearr.append(table->listBookedItem[i]->getName());
        pricearr.append(table->listBookedItem[i]->getPrice());
        quantityarr.append(QString::number(table->listBookedItem[i]->getQuantity()));
        costarr.append(QString::number(table->listBookedItem[i]->getPrice().toInt() * table->listBookedItem[i]->getQuantity()));


        QTableWidgetItem *ordinalarr_element = new QTableWidgetItem(ordinalarr[i]);
        QTableWidgetItem *namearr_element = new QTableWidgetItem(namearr[i]);
        QTableWidgetItem *pricearr_element = new QTableWidgetItem(pricearr[i]);
        QTableWidgetItem *quantityarr_element = new QTableWidgetItem(quantityarr[i]);
        QTableWidgetItem *costarr_element = new QTableWidgetItem(costarr[i]);

        ordinalarr_element->setTextAlignment(Qt::AlignCenter);
        namearr_element->setTextAlignment(Qt::AlignCenter);
        pricearr_element->setTextAlignment(Qt::AlignCenter);
        quantityarr_element->setTextAlignment(Qt::AlignCenter);
        costarr_element->setTextAlignment(Qt::AlignCenter);

        ordinalWidget.append(ordinalarr_element);
        nameWidget.append(namearr_element);
        priceWidget.append(pricearr_element);
        quantityWidget.append(quantityarr_element);
        costWidget.append(costarr_element);

        newtable->setItem(i,0,ordinalWidget[i]);
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
