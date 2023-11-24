#include "billwindow.h"
#include "ui_billwindow.h"
#include "employeewindow.h"
#include "ui_employeewindow.h"
#include "ui_billwindow.h"
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

    // Tạo tên của hàng và lời cảm ơn
    QLabel *logo = new QLabel();
    QLabel *thankyou = new QLabel();
    logo->setText("Group 5 's Restaurant");
    logo->setStyleSheet("color: white;");
    thankyou->setText("Thank you so much!!!");
    thankyou->setStyleSheet("color: white;");
    QFont font;
    font.setFamily("vivaldi");
    font.setPointSize(25);
    thankyou->setFont(font);
    logo->setFont(font);
    thankyou->setAlignment(Qt::AlignCenter);
    logo->setAlignment(Qt::AlignCenter);

    // Tạo hàng tính tổng số tiền

    // Tạo layout chứa hàng tổng tiền
    QLabel *background = new QLabel(ui->centralwidget);
    background->setPixmap(QPixmap(":/BillBackground.png").scaled(QSize(w,h), Qt::KeepAspectRatio));
    background->setGeometry(0,0,w,h);
    QWidget *totalLayoutWidget = new QWidget();
    totalLayoutWidget->setFixedSize(w*0.45, 50);
    QHBoxLayout *totalLayout = new QHBoxLayout(totalLayoutWidget);

    // Tạo label chữ total và label tổng tiền
    QLabel *lbl_cost = new QLabel(totalLayoutWidget);
    lbl_cost->setStyleSheet("color: white;font-size: 16px;");
    QLabel *lbl_cost_value = new QLabel(totalLayoutWidget);
    lbl_cost_value->setStyleSheet("color: white;font-size: 16px;");
    lbl_cost->setText("Total");

    // Từ các món ăn đã mua mà tính tổng tiền
    long total_cost = 0;
    for(int i = 0; i<table->listBoughtItem.size();i++)
    {
        total_cost += table->listBoughtItem[i]->getPrice().toInt()*table->listBoughtItem[i]->getQuantity();
    }
    lbl_cost_value->setText(QString::number(total_cost) + " VND");

    // Gán 2 label vào QHBoxLayout
    totalLayout->addWidget(lbl_cost);
    totalLayout->addWidget(lbl_cost_value);
    totalLayout->setAlignment(lbl_cost, Qt::AlignLeft);
    totalLayout->setAlignment(lbl_cost_value, Qt::AlignRight);

    // Tạo bảng
    QTableWidget *boughtItemTable = new QTableWidget(ui->centralwidget);
    //boughtItemTable->setStyleSheet("color: white;");
    boughtItemTable->setRowCount(table->listBoughtItem.size());
    boughtItemTable->setColumnCount(5);
    boughtItemTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boughtItemTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boughtItemTable->verticalHeader()->setVisible(false);
    boughtItemTable->horizontalHeader()->setStretchLastSection(true);
    boughtItemTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    boughtItemTable->setSelectionMode(QAbstractItemView::NoSelection);
    boughtItemTable->setColumnWidth(0,0.01*w);
    boughtItemTable->setColumnWidth(1,0.2*w);
    boughtItemTable->setColumnWidth(2,0.08*w);
    boughtItemTable->setColumnWidth(3,0.06*w);

    boughtItemTable->setHorizontalHeaderLabels(QStringList()<< "STT" << "Name"<<"Price"<<"Number" << "Cost");
    boughtItemTable->horizontalHeader()->setStyleSheet("QHeaderView::section { border: 1px solid black; background-color: rgba(201, 201, 201, 0.5);}");


    // Du lieu in vao bang
    QList <QString> ordinalArr;
    QList <QString> nameArr;
    QList <QString> priceArr;
    QList <QString> quantityArr;
    QList <QString> costArr;

    QList <QTableWidgetItem *> ordinalWidget;
    QList <QTableWidgetItem *> nameWidget;
    QList <QTableWidgetItem *> priceWidget;
    QList <QTableWidgetItem *> quantityWidget;
    QList <QTableWidgetItem *> costWidget;

    // Tao layout va gan bang vao layout
    boughtItemTable->setFixedSize(w*0.45 + 10, (table->listBoughtItem.size()*50 + 20) > 0.75*h ? 0.7*h : table->listBoughtItem.size()*50 + 20);
    boughtItemTable->setStyleSheet("background-color:transparent;"
                                   "color: white;"
                                   "font-weight: bolder;"
                                   "font-size: 17px");
    QWidget *a = new QWidget(ui->centralwidget);
    a->setGeometry(w/2,0,w/2 + 10,h);
    QVBoxLayout *horizontalLayoutWidget = new QVBoxLayout(a);

    // Hàng logo
    horizontalLayoutWidget->addWidget(logo,0,Qt::AlignCenter);

    // Hàng bảng tính tiền
    horizontalLayoutWidget->addWidget(boughtItemTable,0,Qt::AlignCenter);

    // Hàng tính tổng cộng tiền
    horizontalLayoutWidget->addWidget(totalLayoutWidget,0,Qt::AlignCenter);

    // Hàng dòng cảm ơn
    horizontalLayoutWidget->addWidget(thankyou,0,Qt::AlignCenter);
    horizontalLayoutWidget->setSpacing(5);
    horizontalLayoutWidget->setAlignment(Qt::AlignCenter | Qt::AlignTop);

    for(int i = 0;i<table->listBoughtItem.size();i++)
    {
        boughtItemTable->setRowHeight(i,50);
        ordinalArr.append(QString::number(i + 1));
        nameArr.append(table->listBoughtItem[i]->getName());
        priceArr.append(table->listBoughtItem[i]->getPrice());
        quantityArr.append(QString::number(table->listBoughtItem[i]->getQuantity()));
        costArr.append(QString::number(table->listBoughtItem[i]->getPrice().toInt() * table->listBoughtItem[i]->getQuantity()));


        QTableWidgetItem *ordinalArr_element = new QTableWidgetItem(ordinalArr[i]);
        QTableWidgetItem *nameArr_element = new QTableWidgetItem(nameArr[i]);
        QTableWidgetItem *priceArr_element = new QTableWidgetItem(priceArr[i]);
        QTableWidgetItem *quantityArr_element = new QTableWidgetItem(quantityArr[i]);
        QTableWidgetItem *costArr_element = new QTableWidgetItem(costArr[i]);

        ordinalArr_element->setTextAlignment(Qt::AlignCenter);
        nameArr_element->setTextAlignment(Qt::AlignCenter);
        priceArr_element->setTextAlignment(Qt::AlignCenter);
        quantityArr_element->setTextAlignment(Qt::AlignCenter);
        costArr_element->setTextAlignment(Qt::AlignCenter);

        ordinalWidget.append(ordinalArr_element);
        nameWidget.append(nameArr_element);
        priceWidget.append(priceArr_element);
        quantityWidget.append(quantityArr_element);
        costWidget.append(costArr_element);

        boughtItemTable->setItem(i,0,ordinalWidget[i]);
        boughtItemTable->setItem(i,1,nameWidget[i]);
        boughtItemTable->setItem(i,2,priceWidget[i]);
        boughtItemTable->setItem(i,3,quantityWidget[i]);
        boughtItemTable->setItem(i,4,costWidget[i]);
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
            staff->listTables[i]->listBoughtItem.clear();
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
    employeeWindow1->setStyleSheet("background-color: white;");
    employeeWindow1->show();
    this->hide();
}
