#include "menuorder.h"
#include "ui_menuorder.h"
#include "billwindow.h"
#include "ui_billwindow.h"

menuorder::menuorder(employeeWindow *parent, Table *table) :
    QMainWindow(parent),
    ui(new Ui::menuorder)
{
    this->parent_copy = parent;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    this->table = table;
    ui->setupUi(this);

    // Them nut thanh toan
    QPushButton *payment = new QPushButton(this);
    payment->setText("Payment");
    payment->setStyleSheet(
        "QPushButton {"
        "border-radius: 10px;"
        "border: 1px solid #C6C6C6;"
        "background-color: #CCFFFF;"
        "}"
        "QPushButton:hover {"
        "background-color: #00CCFF;"
        "}"
        );
    payment->move(0.9*w, 0.87*h);

    connect(payment ,&QPushButton::clicked,[=](){
        if(table->listBoughtItem.size() == 0)
            {
                QMessageBox::warning(this, "Warning", "You don't buy anything");
            }
        else
            {
            billwindow *billwindow1 = new billwindow(parent, this->table);
            billwindow1->setAttribute(Qt::WA_DeleteOnClose);

            QScreen *screen = QGuiApplication::primaryScreen();
            QRect geometry = screen->geometry();
            int w = geometry.width();
            int h = geometry.height();
            billwindow1->setGeometry(0,0,w,h);
            billwindow1->move(0,0);
            QFont font("Arial", 13);
            billwindow1->setFont(font);
            billwindow1->show();
            this->hide();
        }
    });

    std::fstream file("listItem.txt", std::ios::in);
    if (file.is_open()) {
        std::string line;
        QString name;
        QString price;
        QString image;
        QString id;
        file.seekg(0, std::ios::end);
        if (file.tellp() != 0)
        {
            file.seekg(0, std::ios::beg);
            while (!file.eof()) {
                std::getline(file, line, '\n');
                std::size_t pos1 = line.find(',');
                std::size_t pos2 = line.find(',', pos1 + 1);
                std::size_t pos3 = line.find(',', pos2 + 1);

                id = QString::fromStdString(line.substr(0, pos1));
                image = QString::fromStdString(line.substr(pos1 + 1, pos2 - pos1 - 1));
                name = QString::fromStdString(line.substr(pos2 + 1, pos3 - pos2 - 1));
                price = QString::fromStdString(line.substr(pos3 + 1));

                Item newItem(name, price, image);
                newItem.setId(id.toInt());
                listitem.push_back(newItem);
            }
        }
        file.close();
    }

    QTableWidget *boughtItemTable = new QTableWidget(ui->centralwidget);
    boughtItemTable->setRowCount(listitem.size());
    boughtItemTable->setColumnCount(4);
    boughtItemTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    boughtItemTable->verticalHeader()->setFixedWidth(0.025*w);
    boughtItemTable->setColumnWidth(0,0.29*w);
    boughtItemTable->setColumnWidth(1,0.28*w);
    boughtItemTable->setColumnWidth(2,0.28*w);
    boughtItemTable->setColumnWidth(3,0.125*w);
    boughtItemTable->setGeometry(0,0,w,0.8*h);

    boughtItemTable->setHorizontalHeaderLabels(QStringList()<<"Image"<< "Name"<<"Price"<<"Quantity");

    QLabel *lbl_cost = new QLabel(ui->centralwidget);
    QLabel *lbl_total = new QLabel(ui->centralwidget);

    lbl_cost->setGeometry(0.875*w, 0.8*h, 0.125*w, 0.1*h);
    lbl_total->setGeometry(0.595*w, 0.8*h, 0.28*w, 0.1*h);
    lbl_cost->setAlignment(Qt::AlignCenter);
    lbl_total->setAlignment(Qt::AlignCenter);

    double temp_cost = 0;
    if(table->listBoughtItem.size() != 0)
    {
        for(int i = 0; i < table->listBoughtItem.size();i++)
        {
            temp_cost += table->listBoughtItem[i]->getPrice().toInt()*table->listBoughtItem[i]->getQuantity();
        }
        lbl_cost->setText(QString::number(temp_cost));
    }
    else
    {
        lbl_cost->setText("0");
    }
    lbl_total->setText("Total");

    QList <QLabel *> imageArr;
    QList <QString> nameArr;
    QList <QString> priceArr;
    QList <QTableWidgetItem *> nameWidget;
    QList <QTableWidgetItem *> priceWidget;

    // Cài đặt Font chữ cho các chữ
    QFont font;
    font.setPointSize(13);

    for(int i = 0;i <listitem.size();i++)
    {
        QLabel *ImageLabel = new QLabel();
        ImageLabel->setPixmap(QPixmap(listitem[i].getImage()));
        ImageLabel->setScaledContents(true);
        imageArr.append(ImageLabel);
        nameArr.append(listitem[i].getName());
        priceArr.append(listitem[i].getPrice());

        QTableWidgetItem *nameArr_element = new QTableWidgetItem(nameArr[i]);
        QTableWidgetItem *priceArr_element = new QTableWidgetItem(priceArr[i]);
        nameArr_element->setTextAlignment(Qt::AlignCenter);
        priceArr_element->setTextAlignment(Qt::AlignCenter);
        nameWidget.append(nameArr_element);
        priceWidget.append(priceArr_element);
        boughtItemTable->setRowHeight(i,150);

        boughtItemTable->setItem(i,1,nameWidget[i]);
        boughtItemTable->setCellWidget(i,0,imageArr[i]);
        boughtItemTable->setItem(i,2,priceWidget[i]);

        QWidget *numberLayoutWidget = new QWidget(ui->centralwidget);
        QHBoxLayout *horizontalLayoutWidget = new QHBoxLayout(numberLayoutWidget);
        QPushButton *subButton = new QPushButton(numberLayoutWidget);
        subButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        subButton->setIcon(icon);
        subButton->setAutoRepeat(false);
        QLabel *numberlbl = new QLabel(numberLayoutWidget);
        if(table->listBoughtItem.size() != 0)
        {
            int temp = 0;
            for(int j = 0;j < table->listBoughtItem.size();j++)
            {
                if(listitem[i].getId() == (table->listBoughtItem[j]->getId()))
                {
                    numberlbl->setText(QString::number(table->listBoughtItem[j]->getQuantity()));
                    temp = 1;
                    break;
                }
            }
            if(temp == 0) numberlbl->setText("0");
        }
        else
        {
            numberlbl->setText("0");
        }
        QPushButton *addButton = new QPushButton(numberLayoutWidget);

        addButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
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
        addButton->setIcon(icon1);
        addButton->setAutoRepeat(false);

        horizontalLayoutWidget->addWidget(subButton);
        horizontalLayoutWidget->addWidget(numberlbl);
        horizontalLayoutWidget->addWidget(addButton);
        boughtItemTable->setCellWidget(i,3,numberLayoutWidget);
    QObject::connect(addButton, &QPushButton::clicked, [=]() {
        lbl_cost->setText(QString::number(lbl_cost->text().toInt() + listitem[i].getPrice().toInt()));
        numberlbl->setText(QString::number(numberlbl->text().toInt() + 1));
            int temp = 0;
            for (int j = 0; j < table->listBoughtItem.size(); j++) {
                if (listitem[i].getId() == table->listBoughtItem[j]->getId())
                {
                    temp = 1;
                    table->listBoughtItem[j]->setQuantity(numberlbl->text().toInt());
                    break;
                }
            }

            if(temp != 1)
            {
                BoughtItem *boughtItem = new BoughtItem(listitem[i].getName(), listitem[i].getId(), listitem[i].getPrice(), numberlbl->text().toInt());
                table->listBoughtItem.push_back(boughtItem);
            }

    });



        QObject::connect(subButton, &QPushButton::clicked, [=]() {

            if(numberlbl->text().toInt() > 0) lbl_cost->setText(QString::number(lbl_cost->text().toInt() - listitem[i].getPrice().toInt()));
            numberlbl->setText(QString::number(numberlbl->text().toInt() == 0 ? 0 :numberlbl->text().toInt() - 1));

            for(int j = 0; j < table->listBoughtItem.size();j++)
            {
                if(listitem[i].getId() == table->listBoughtItem[j]->getId())
                    if(table->listBoughtItem[j]->getQuantity() == 1)
                    {
                        table->listBoughtItem.erase(table->listBoughtItem.begin() + j);
                    }
                    else
                    {
                        table->listBoughtItem[j]->setQuantity(numberlbl->text().toInt());
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

    // cap nhat lai listTable moi
        if(table->listBoughtItem.size() != 0)
        {
            for(int i = 0;i < parent_copy->staff->listTables.size();i++)
            {
                if(parent_copy->staff->listTables[i]->getOrdinal() == table->getOrdinal())
                {
                parent_copy->staff->listTables[i]->setStatus(0);
                }
            }
        }
        else
        {
            for(int i = 0;i < parent_copy->staff->listTables.size();i++)
            {
                if(parent_copy->staff->listTables[i]->getOrdinal() == table->getOrdinal())
                {
                parent_copy->staff->listTables[i]->setStatus(1);
                }
            }
        }

    // Luu lai listTable moi vao file text
    list_table.open("listTable.txt", std::ios::trunc |std::ios::out);
    if(list_table.is_open() && !list_table.eof()){
        list_table.seekp(0);
        for(int i = 0;i < parent_copy->staff->listTables.size();i++){
                list_table << parent_copy->staff->listTables[i]->getOrdinal()
                 << "-"
                 << parent_copy->staff->listTables[i]->getStatus()
                 << std::endl;
        }

    }

    else
    {
        for(int i = 0;i < parent_copy->staff->listTables.size();i++){
        list_table << std::endl
             << QString::number(parent_copy->staff->listTables[i]->getOrdinal()).toStdString()
             << "-"
        << parent_copy->staff->listTables[i]->getStatus();
        }
    }

    employeeWindow* employeeWindow1 = new employeeWindow(parent_copy->staff,this);
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
