#include "menuorder.h"
#include "ui_menuorder.h"
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

menuorder::menuorder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menuorder)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    ui->setupUi(this);
    this->setGeometry(0,0,w,h);
    this->move(0,0);


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
    newtable->setGeometry(0,0,w,0.8*h);

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
        numberlbl->setText("0");
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
            numberlbl->setText(QString::number(numberlbl->text().toInt() + 1));
            lbl_cost->setText(QString::number(lbl_cost->text().toInt() + listitem[i].getPrice().toInt()));
            if(listboughtitem.size() == 0)
            {
                BoughtItem newboughtitem = BoughtItem(listitem[i].getName(), listitem[i].getId(), listitem[i].getPrice(),numberlbl->text().toInt());
                listboughtitem.push_back(newboughtitem);
            }
            else
            {
                BoughtItem abc = BoughtItem("a", 5, "b",7);
                //BoughtItem abc = BoughtItem(a[i].getName(), a[i].getId(), a[i].getPrice(),numberlbl->text().toInt());
                for(int j = 0; j < listboughtitem.size();j++)
                {
                    if(listitem[i].getId() == listboughtitem[j].getId()) listboughtitem[j].setQuantity(numberlbl->text().toInt());
                    else
                    {
                        listboughtitem.push_back(abc);
                        break;
                    }
                }
            }
        });

        QObject::connect(pushButton1, &QPushButton::clicked, [=]() {

            if(numberlbl->text().toInt() > 0) lbl_cost->setText(QString::number(lbl_cost->text().toInt() - listitem[i].getPrice().toInt()));
            numberlbl->setText(QString::number(numberlbl->text().toInt() == 0 ? 0 :numberlbl->text().toInt() - 1));

            for(int j = 0; j < listboughtitem.size();j++)
            {
                if(listitem[i].getId() == listboughtitem[j].getId())
                    if(listboughtitem[j].getQuantity() == 1)
                    {
                        listboughtitem.erase(listboughtitem.begin() + j);
                    }
                    else
                    {
                        listboughtitem[j].setQuantity(numberlbl->text().toInt());
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

    std::fstream file;
    file.open("listBoughtItem.txt", std::ios::in |std::ios::out);
    if(file.is_open() && !file.eof()){
        file.seekp(0);
        for(int i = 0;i < listboughtitem.size();i++){
            file << listboughtitem[i].getName().toStdString()
                 << "-"
                 << QString::number(listboughtitem[i].getId()).toStdString()
                 << "-"
                 << listboughtitem[i].getPrice().toStdString()
                 << "-"
                 << QString::number(listboughtitem[i].getQuantity()).toStdString()
                 << std::endl;
        }

    }
    else
    {
        for(int i = 0;i < listboughtitem.size();i++){
            file << std::endl
                 << listboughtitem[i].getName().toStdString()
                 << "-"
                 << QString::number(listboughtitem[i].getId()).toStdString()
                 << "-"
                 << listboughtitem[i].getPrice().toStdString()
                 << "-"
                 << QString::number(listboughtitem[i].getQuantity()).toStdString();


        }
    }
    file.close();
    this->close();
}
