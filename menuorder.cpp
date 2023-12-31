#include "menuorder.h"
#include "ui_menuorder.h"

menuorder::menuorder(employeeWindow *parent, Table *table) : QMainWindow(parent),ui(new Ui::menuorder)
{
    ui->setupUi(this);
    this->parent_copy = parent;
    this->table = table;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();

    std::fstream file("listItem.txt", std::ios::in);
    if (file.is_open())
    {
        std::string line;
        QString name;
        QString price;
        QString image;
        QString id;
        file.seekg(0, std::ios::end);
        if (file.tellp() != 0)
        {
            file.seekg(0, std::ios::beg);
            while (!file.eof())
            {
                std::getline(file, line, '\n');
                std::size_t pos1 = line.find(',');
                std::size_t pos2 = line.find(',', pos1 + 1);
                std::size_t pos3 = line.find(',', pos2 + 1);

                id = QString::fromStdString(line.substr(0, pos1));
                image = QString::fromStdString(line.substr(pos1 + 1, pos2 - pos1 - 1));
                name = QString::fromStdString(line.substr(pos2 + 1, pos3 - pos2 - 1));
                price = QString::fromStdString(line.substr(pos3 + 1)).removeLast();

                Item newItem(name, price, image);
                newItem.setId(id.toInt());
                listitem.push_back(newItem);
            }
        }
        file.close();
    }

    QWidget *mainLayoutWidget = new QWidget(ui->centralwidget);
    mainLayoutWidget->setGeometry(0, 0, w, h);
    QHBoxLayout *mainLayout = new QHBoxLayout(mainLayoutWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    QWidget *costWidget = new QWidget(ui->centralwidget);
    QHBoxLayout *costLayout = new QHBoxLayout(costWidget);
    QLabel *lblCostValue = new QLabel(costWidget);
    QLabel *lblCostUnit = new QLabel(costWidget);
    lblCostUnit->setText("VND");
    costLayout->addWidget(lblCostValue);
    costLayout->addWidget(lblCostUnit);
    costWidget->setLayout(costLayout);
    costWidget->setGeometry(0.9 * w, 0.8 * h, 0.125 * w, 0.1 * h * 0.5);
    costWidget->setStyleSheet("color: white;"
                              "font-size: 17px;");

    QLabel *lbl_total = new QLabel(mainLayoutWidget);
    lbl_total->setGeometry(0.73 * w, 0.8 * h, 0.28 * w * 0.5, 0.1 * h * 0.5);
    lbl_total->setAlignment(Qt::AlignCenter);
    lbl_total->setText("Total");
    lbl_total->setStyleSheet("color: white;"
                             "font-size: 17px;");

    QLabel *menuorderPicture = new QLabel(mainLayoutWidget);
    menuorderPicture->setPixmap(QPixmap(":/background/menuOrderImage.jpg").scaled(QSize(w / 3, h)));

    QTableWidget *boughtItemTable = new QTableWidget(mainLayoutWidget);
    boughtItemTable->setShowGrid(false);
    boughtItemTable->setStyleSheet("background-color: #101010;"
                                   "color: white;"
                                   "font-size: 17px;"
                                   "border: 8px solid #101010;");
    boughtItemTable->setColumnCount(4);
    boughtItemTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    boughtItemTable->verticalHeader()->setFixedWidth(0);
    boughtItemTable->horizontalHeader()->hide();
    boughtItemTable->setColumnWidth(0, 2 * 0.2 * w / 3);
    boughtItemTable->setColumnWidth(1, 2 * 0.3 * w / 3);
    boughtItemTable->setColumnWidth(2, 2 * 0.3 * w / 3);
    boughtItemTable->setColumnWidth(3, 2 * 0.175 * w / 3);
    boughtItemTable->setFixedSize(2 * w / 3, 0.8 * h);
    boughtItemTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    boughtItemTable->setSelectionMode(QAbstractItemView::NoSelection);

    boughtItemTable->setHorizontalHeaderLabels(QStringList() << "Image"
                                                             << "Name"
                                                             << "Price"
                                                             << "Quantity");
    boughtItemTable->horizontalHeader()->setStyleSheet("background-color: #101010;");

    long temp_cost = 0;
    if (table->listBoughtItem.size() != 0)
    {
        for (int i = 0; i < table->listBoughtItem.size(); i++)
        {
            temp_cost += table->listBoughtItem[i]->getPrice().toInt() * table->listBoughtItem[i]->getQuantity();
        }
        lblCostValue->setText(QString::number(temp_cost));
    }
    else
    {
        lblCostValue->setText("0");
    }

    QList<QLabel *> imageArr;
    QList<QString> nameArr;
    QList<QString> priceArr;
    QList<QTableWidgetItem *> nameWidget;
    QList<QTableWidgetItem *> priceWidget;

    int oldsize = listitem.size();

    if (table->listBoughtItem.size() != 0)
    {
        for (BoughtItem *boughtItem : table->listBoughtItem)
        {
            int temp = 0;
            for (Item item : listitem)
            {
                if (item.getId() == boughtItem->getId())
                {
                    temp = 1;
                    break;
                }
            }
            if (!temp)
            {
                Item newItem(boughtItem->getName(), boughtItem->getPrice(), boughtItem->getImage());
                newItem.setId(boughtItem->getId());
                listitem.push_back(newItem);
            }
        }
    }

    boughtItemTable->setRowCount(listitem.size());

    QLocale locale(QLocale::Vietnamese);

    for (int i = 0; i < listitem.size(); i++)
    {
        QLabel *ImageLabel = new QLabel();
        ImageLabel->setPixmap(QPixmap(listitem[i].getImage()));
        ImageLabel->setAlignment(Qt::AlignCenter);
        ImageLabel->setScaledContents(true);
        imageArr.append(ImageLabel);
        nameArr.append(listitem[i].getName());
        priceArr.append(locale.toCurrencyString(listitem[i].getPrice().toDouble(), "VND"));

        QTableWidgetItem *nameArr_element = new QTableWidgetItem(nameArr[i]);
        nameArr_element->setForeground(Qt::white);
        QTableWidgetItem *priceArr_element = new QTableWidgetItem(priceArr[i]);
        priceArr_element->setForeground(Qt::white);
        nameArr_element->setTextAlignment(Qt::AlignCenter);
        priceArr_element->setTextAlignment(Qt::AlignCenter);
        nameWidget.append(nameArr_element);
        priceWidget.append(priceArr_element);
        boughtItemTable->setRowHeight(i, h / 8);

        boughtItemTable->setItem(i, 1, nameWidget[i]);
        boughtItemTable->setCellWidget(i, 0, imageArr[i]);
        boughtItemTable->setItem(i, 2, priceWidget[i]);

        QWidget *numberLayoutWidget = new QWidget(ui->centralwidget);
        QHBoxLayout *horizontalLayoutWidget = new QHBoxLayout(numberLayoutWidget);
        QLabel *numberlbl = new QLabel(numberLayoutWidget);
        if (table->listBoughtItem.size() != 0)
        {
            int temp = 0;
            for (int j = 0; j < table->listBoughtItem.size(); j++)
            {
                if (listitem[i].getId() == (table->listBoughtItem[j]->getId()))
                {
                    numberlbl->setText(QString::number(table->listBoughtItem[j]->getQuantity()));
                    temp = 1;
                    break;
                }
            }
            if (temp == 0)
                numberlbl->setText("0");
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
                                                   "background-color: #101010;\n"
                                                   "border: black solid 2px;\n"
                                                   "color : Black;\n"
                                                   "font-weight: bolder;\n"
                                                   "}\n"
                                                   ""));
        QIcon addIcon;
        addIcon.addFile(QString::fromUtf8(":/icon/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(addIcon);
        addButton->setAutoRepeat(false);

        QPushButton *subButton = new QPushButton(numberLayoutWidget);
        subButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
                                                   "border-radius:50%;\n"
                                                   "height:100%;\n"
                                                   "width: 100%;\n"
                                                   "background-color: #101010;\n"
                                                   "border: black solid 2px;\n"
                                                   "color : Black;\n"
                                                   "font-weight: bolder;\n"
                                                   "}\n"
                                                   ""));
        QIcon subIcon;
        subIcon.addFile(QString::fromUtf8(":/icon/sub.png"), QSize(), QIcon::Normal, QIcon::Off);
        subButton->setIcon(subIcon);
        subButton->setAutoRepeat(false);

        horizontalLayoutWidget->addWidget(subButton);
        horizontalLayoutWidget->addWidget(numberlbl);
        horizontalLayoutWidget->addWidget(addButton);
        boughtItemTable->setCellWidget(i, 3, numberLayoutWidget);
        QObject::connect(addButton, &QPushButton::clicked, [=]()
        {
            if(i >= oldsize)
            {
                QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning, "Warning", "This item is sold out!!",QMessageBox::Ok, this);
                msgBox->setStyleSheet("background-color: white;"
                                      "font-size: 17px;");
                msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
                msgBox->open();
            }
            else
            {
                lblCostValue->setText(QString::number(lblCostValue->text().toLong() + listitem[i].getPrice().toInt()));
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
                    BoughtItem *boughtItem = new BoughtItem(listitem[i].getImage(), listitem[i].getName(), listitem[i].getId(), listitem[i].getPrice(), numberlbl->text().toInt());
                    table->listBoughtItem.push_back(boughtItem);
                }
            } });

        QObject::connect(subButton, &QPushButton::clicked, [=]()
        {
            if(numberlbl->text().toInt() > 0) lblCostValue->setText(QString::number(lblCostValue->text().toLong() - listitem[i].getPrice().toInt()));
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
            } });
    }

    mainLayout->addWidget(menuorderPicture);
    mainLayout->addWidget(boughtItemTable);
    mainLayout->setAlignment(boughtItemTable, Qt::AlignTop);

    QWidget *searchWidget = new QWidget(this);
    searchWidget->resize(300, 60);
    searchWidget->move(w / 3 + 5, 0.85 * h - 5);
    QHBoxLayout *layoutSearch = new QHBoxLayout(searchWidget);
    QLabel *searchLabel = new QLabel(searchWidget);
    searchLabel->setText("Search");
    searchLabel->setStyleSheet("color: white;"
                               "font-size: 17px;");
    QLineEdit *filter = new QLineEdit();
    filter->addAction(QIcon(":/icon/search.png"), QLineEdit::LeadingPosition);
    filter->setStyleSheet("border-radius: 5px;"
                          "border: 2px solid white;"
                          "color: white;"
                          "font-size: 17px;");
    layoutSearch->addWidget(searchLabel);
    layoutSearch->addWidget(filter);
    searchWidget->setLayout(layoutSearch);

    QObject::connect(filter, &QLineEdit::textChanged, [=](const QString &text)
    {
        for(int i = 0; i < listitem.size();i++)
        {
            if(!boughtItemTable->item(i,1)->text().contains(text, Qt::CaseInsensitive))
            {
                boughtItemTable->setRowHidden(i, true);
            }
            else
            {
                boughtItemTable->setRowHidden(i, false);
            }
        } });

    QPushButton *payment = new QPushButton(this);
    payment->setText("Payment");
    payment->setIcon(QIcon(":/icon/paymentIcon.png"));
    payment->resize(100, 40);
    payment->setStyleSheet(
        "QPushButton {"
        "font-weight: bold;"
        "color: black;"
        "border-radius: 10px;"
        "border: 1px solid black;"
        "background-color: #C0C0C0;"
        "}"
        "QPushButton:hover {"
        "background-color: #808080;"
        "}");
    payment->move(0.9 * w, 0.85 * h);

    connect(payment, &QPushButton::clicked, [=]()
    {
        if(table->listBoughtItem.size() == 0)
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning, "Warning", "You don't buy anything",QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");
            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();
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
            billwindow1->setStyleSheet("background-color: transparent;");
            billwindow1->show();
            this->hide();
        } });
}

menuorder::~menuorder()
{
    delete ui;
}

void menuorder::closeEvent(QCloseEvent *event)
{
    event->ignore();
    std::fstream list_table;

    if (table->listBoughtItem.size() != 0)
    {
        for (int i = 0; i < parent_copy->staff->listTables.size(); i++)
        {
            if (parent_copy->staff->listTables[i]->getOrdinal() == table->getOrdinal())
            {
                parent_copy->staff->listTables[i]->setStatus(0);
            }
        }
    }
    else
    {
        for (int i = 0; i < parent_copy->staff->listTables.size(); i++)
        {
            if (parent_copy->staff->listTables[i]->getOrdinal() == table->getOrdinal())
            {
                parent_copy->staff->listTables[i]->setStatus(1);
            }
        }
    }

    list_table.open("listTable.txt", std::ios::trunc | std::ios::out);
    if (list_table.is_open() && !list_table.eof())
    {
        list_table.seekp(0);
        for (int i = 0; i < parent_copy->staff->listTables.size(); i++)
        {
            list_table << parent_copy->staff->listTables[i]->getOrdinal()
                       << "-"
                       << parent_copy->staff->listTables[i]->getStatus()
                       << std::endl;
        }
    }

    else
    {
        for (int i = 0; i < parent_copy->staff->listTables.size(); i++)
        {
            list_table << std::endl
                       << QString::number(parent_copy->staff->listTables[i]->getOrdinal()).toStdString()
                       << "-"
                       << parent_copy->staff->listTables[i]->getStatus();
        }
    }

    employeeWindow *employee = new employeeWindow(parent_copy->staff, this);
    employee->setAttribute(Qt::WA_DeleteOnClose);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    employee->setGeometry(0, 0, w, h);
    employee->move(0, 0);
    employee->setStyleSheet("background-color: white;");
    employee->show();
    list_table.close();
    this->hide();
}
