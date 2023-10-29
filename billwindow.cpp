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
billwindow::billwindow(QWidget *parent, Table *table) :
    QMainWindow(parent),
    ui(new Ui::billwindow)
{
    //int a = table->listBookedItem.size();
    //qDebug() << a;
    this->table = table;
    //QWidget *widget = new QWidget(ui->centralwidg);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();

    ui->setupUi(this);
    int cost = 200000;

    QLabel *logo = new QLabel();
    logo->setText("Group 5 's Restaurant");
    QFont font;
    font.setFamily("vivaldi");
    font.setPointSize(20);
    logo->setFont(font);
    logo->setAlignment(Qt::AlignCenter);


  // tao bang
  QTableWidget *newtable = new QTableWidget(ui->centralwidget);
  newtable->setRowCount(table->listBookedItem.size());
  newtable->setColumnCount(5);
  newtable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  newtable->verticalHeader()->setVisible(false);
  newtable->setColumnWidth(0,0.01*w);
  newtable->setColumnWidth(1,0.17*w);
  newtable->setColumnWidth(2,0.17*w);
  newtable->setColumnWidth(3,0.05*w);
  newtable->setColumnWidth(4,0.17*w);
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
    newtable->setFixedSize(w/2, table->listBookedItem.size()*80);
    //QWidget *layoutWidget = new QWidget();
    QVBoxLayout *horizontalLayoutWidget = new QVBoxLayout(ui->centralwidget);
    //horizontalLayoutWidget->setSizeConstraint(QLayout::SetFixedSize);
    horizontalLayoutWidget->addWidget(logo,0,Qt::AlignCenter);
    horizontalLayoutWidget->addWidget(newtable,0,Qt::AlignCenter);
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

    std::fstream list_table;
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

    r_file.close();

    // cap nhat lai listTable moi
    if(table->listBookedItem.size() != 0)
    {
        for(auto _table : updateListTable)
        {
            if(_table->getOrdinal() == table->getOrdinal()) _table->setStatus(1);
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
    list_table.close();
    this->hide();
}
