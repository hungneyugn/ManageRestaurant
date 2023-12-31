#include "managerwindow.h"
#include "ui_managerwindow.h"


ManagerWindow::ManagerWindow(QWidget *parent, employeeWindow *employee) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)

{
    ui->setupUi(this);
    this->employee = employee;
    QFont font;
    QFont fontNoti;
    QFont fontNumber;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();

    ui->backgroundlbl->setGeometry(0,0,w/2 - 20,h);
    ui->backgroundlbl->move(0,0);

    QLocale locale(QLocale::Vietnamese, QLocale::Vietnam);

    font.setPointSize(13);
    fontNoti.setPointSize(11);
    fontNumber.setPointSize(11);
    fontNumber.setWordSpacing(5);

    tableItem = new QTableWidget(ui->centralwidget);
    tableItem -> setRowCount(manager->listItems.size());
    ui->centralwidget->setStyleSheet("background-color: #101010;"
                                     "color: white;"
                                     "border: #101010;");

    tableItem -> setColumnCount(3);
    tableItem -> setGeometry(w/2,h/10,7*w/9,3*h/4);
    tableItem->setStyleSheet("QTableWidget::item {border:1px solid white; color: white;}");

    tableItem -> setHorizontalHeaderLabels(QStringList() <<"Image" << "Name" << "Price");
    tableItem->horizontalHeader()->setFont(font);

    tableItem->setColumnWidth(0, w/9);
    tableItem->setColumnWidth(1, w/6);
    tableItem->setColumnWidth(2, w/6);

    ui->btn_add->move(w/8,7*h/12);
    ui->btn_add->setStyle(QStyleFactory::create("Fusion"));
    ui->btn_add->setStyleSheet("QPushButton {"
                               "color: black;"
                               "border-radius: 10px;"
                               "border: 1px solid black;"
                               "background-color: #C0C0C0;"
                               "}"
                               "QPushButton:hover {"
                               "background-color: #808080;"
                               "}");

    ui->btn_save->move(w/8,8*h/12);
    ui->btn_save->setStyle(QStyleFactory::create("Fusion"));
    ui->btn_save->setStyleSheet("QPushButton {"
                                "color: black;"
                                "border-radius: 10px;"
                                "border: 1px solid black;"
                                "background-color: #C0C0C0;"
                                "}"
                                "QPushButton:hover {"
                                "background-color: #808080;"
                                "}");

    ui->btn_delete->move(w/4,7*h/12);
    ui->btn_delete->setStyle(QStyleFactory::create("Fusion"));
    ui->btn_delete->setStyleSheet("QPushButton {"
                                  "color: black;"
                                  "border-radius: 10px;"
                                  "border: 1px solid black;"
                                  "background-color: #C0C0C0;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #808080;"
                                  "}");

    ui->btn_update->move(w/4,2*h/3);
    ui->btn_update->setStyle(QStyleFactory::create("Fusion"));
    ui->btn_update->setStyleSheet("QPushButton {"
                                  "color: black;"
                                  "border-radius: 10px;"
                                  "border: 1px solid black;"
                                  "background-color: #C0C0C0;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #808080;"
                                  "}");

    for (int i = 0; i < manager->listItems.size() ; i++)
    {
        QString formatPrice = locale.toCurrencyString(manager->listItems[i].getPrice().toDouble(), "VND");
        QTableWidgetItem *nameTableWidget = new QTableWidgetItem(manager->listItems[i].getName());
        QTableWidgetItem *priceTableWidget = new QTableWidgetItem(formatPrice);

        nameTableWidget -> setTextAlignment(Qt::AlignCenter);
        priceTableWidget -> setTextAlignment(Qt::AlignCenter);

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

    tableItem->verticalHeader()->setVisible(false);
    tableItem->horizontalHeader()->setVisible(false);

    QTextEdit *numtable = new QTextEdit(this);
    numtable->setGeometry(w/8,h/2,171,41);
    numtable->setFont(fontNumber);
    numtable->setAlignment(Qt::AlignHCenter);
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
                                    "border-radius: 10px;"
                                    "border: 1px solid black;"
                                    "background-color: #C0C0C0;"
                                    "}"
                                    "QPushButton:hover {"
                                    "background-color: #808080;"
                                    "}"
                                    );

    int number= 0;
    std::fstream r_file("listTable.txt", std::ios::in);
    std::string line_r;
    if (r_file.is_open())
    {
        while (std::getline(r_file, line_r))
            number++;
    }
    r_file.close();

    if(number != 0)
    {
        numtable->setText(QString::number(number));
        numtable->setAlignment(Qt::AlignHCenter);
    }

    connect(createtablebutton,&QPushButton::clicked,[=]()
    {
        QRegularExpression regex("[a-zA-Z!@#$%^&*<>?+=-_`~.,* ]+");
        if (numtable->toPlainText().isEmpty()|| regex.match(numtable->toPlainText()).hasMatch()|| numtable->toPlainText().toInt()<=0)
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning, "Warning", "Please enter number of table",
                                                  QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");

            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();

            numtable->setText(QString::number(number));
            numtable->setAlignment(Qt::AlignHCenter);
        }
        else if (numtable->toPlainText().toInt()>154)
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning, "Warning", "Maximum number of table : 154 ",
                                                  QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");

            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();

            numtable->setText(QString::number(number));
            numtable->setAlignment(Qt::AlignHCenter);
        }
        else
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "", "Updated number of table successfully ",
                                                  QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");

            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();

            int num = numtable->toPlainText().toInt() ;
            std::ofstream file("listTable.txt", std::ios::trunc);
            for (int i = 0; i<num;i++)
                file <<i+1<<"-"<<"1"<<std::endl;
            file.close();
        }
    });

    connect(tableItem, &QTableWidget::itemChanged, [=](QTableWidgetItem *item)
    {
        uint8_t num = 0;
        if (item && item->column() == 2)
        {
            if (!item->text().isEmpty())
            {
                for (int i = 0; i < item->text().size(); i++)
                {
                    if (item->text().at(i).isDigit() == 0 )
                        num++;
                }

                if (num == 0)
                    item->setText(locale.toCurrencyString(item->text().toDouble(), "VND"));
                else if (item->text().size() > 0 || item->text().contains("VND"))
                {
                    uint8_t num1 = 0;
                    QString temp = item->text().replace("VND", "").replace(".", "");
                    if (temp.size() > 1)
                    {
                        for (int i = 0; i < temp.size() - 1; i++)
                        {
                            if (temp.at(i).isDigit() == 0)
                                num1++;
                        }
                        if (num1 != 0)
                        {
                            QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error", "Please enter price in number!",
                                                                  QMessageBox::Ok, this);
                            msgBox->setStyleSheet("background-color: white;"
                                                  "font-size: 17px;");

                            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
                            msgBox->open();
                        }
                        else
                            item->setText(locale.toCurrencyString(temp.toDouble(), "VND"));
                    }
                    else
                    {
                        QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error", "Please enter price in number!",
                                                              QMessageBox::Ok, this);
                        msgBox->setStyleSheet("background-color: white;"
                                              "font-size: 17px;");

                        msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
                        msgBox->open();
                    }
                }
            }
        }
    });
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::closeEvent(QCloseEvent *event){
    MainWindow *mainwindow = new MainWindow(this->employee);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int w = geometry.width();
    int h = geometry.height();
    if (tableItem->rowCount() > manager->listItems.size())
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Question, "Information", "Do you want to save changes?",
                                              QMessageBox::Yes | QMessageBox::No, this);
        msgBox->setStyleSheet("background-color: white;"
                              "font-size: 17px;");

        msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        msgBox->open();

        if (msgBox->exec() == QMessageBox::Yes)
            ManagerWindow::on_btn_save_clicked();
    }

    mainwindow->setGeometry(0,0,w,h);
    mainwindow->move(0,0);
    mainwindow->show();
    this->hide();
}

void ManagerWindow::uploadImage()
{
    QString destinationFolderName = "image";
    QString imagePath = QFileDialog::getOpenFileName(this, "Choose an image", QDir::homePath(), "Ảnh (*.png *.jpg *.jpeg)");

    QString fileName = QFileInfo(imagePath).fileName();
    QString currentPath = QDir::currentPath();

    QString destinationPath = currentPath + "/" + destinationFolderName;
    QString destinationFilePath = destinationPath + "/" + fileName;
    this->image_add = destinationFilePath;
    if (fileName != "")
    {
        if (QDir(destinationPath).exists() || QDir().mkpath(destinationPath))
        {
            QFile::copy(imagePath, destinationFilePath);
        }
    }
    else
        this->image_add = "";
    QIcon icon(image_add);
    newButton->setIcon(icon);
    newButton->setText("");
    newButton->setIconSize(newButton->size());
}

void ManagerWindow::on_btn_add_clicked()
{
    QFont font;
    font.setPointSize(13);

    QTableWidgetItem *item1 = new QTableWidgetItem("");
    QTableWidgetItem *item2 = new QTableWidgetItem("");

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();
    int h = geometry.height();
    tableItem->insertRow(tableItem->rowCount());

    int row = tableItem->rowCount();
    tableItem->setItem(row - 1, 1, item1);
    tableItem->setItem(row - 1, 2, item2);

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
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error", "Please enter the data!",
                                              QMessageBox::Ok, this);
        msgBox->setStyleSheet("background-color: white;"
                              "font-size: 17px;");

        msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        msgBox->open();
    }
    else
    {
        QString name = tableItem->item(rowCount, 1)->text();
        QString price = tableItem->item(rowCount, 2)->text();
        QString image = image_add;
        QString new_price = price.replace("VND", "").replace(".", "");

        if (name.isEmpty() || new_price.isEmpty() || image.isEmpty())
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error", "Please enter the data!",
                                                  QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");

            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();
        }
        else if ((manager->listItems.size() != 0) && (manager->checkExistNameItem(name) == 0))
        {
            Item newItem(name, new_price, image);
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
            if(file.is_open())
            {
                file << std::endl << id.toStdString() << ","
                                  << image.toStdString() << ","
                                  << name.toStdString() << ","
                                  << new_price.toStdString();
            }
            file.close();
        }
        else if (manager->listItems.size() == 0)
        {
            Item newItem(name, new_price, image);
            newItem.setId(99,1);
            QString id = QString::number(newItem.getId());
            QTableWidgetItem *itemName = tableItem->item(rowCount, 1);
            QTableWidgetItem *itemPrice = tableItem->item(rowCount, 2);
            itemName->setTextAlignment(Qt::AlignCenter);
            itemPrice->setTextAlignment(Qt::AlignCenter);
            this ->manager->listItems.push_back(newItem);

            std::fstream file;
            file.open("listItem.txt", std::ios::app);
            file << id.toStdString() << ","
                 << image.toStdString() << ","
                 << name.toStdString() << ","
                 << new_price.toStdString();
            file.close();
        }
        else if(manager->checkExistNameItem(name) == 1)
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error", "The food has existed!",
                                                  QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");

            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();
        }
    }
}

void ManagerWindow::on_btn_delete_clicked()
{
    bool isItemSelected = tableItem->selectionModel()->hasSelection();
    int row = this->tableItem->currentRow();
    QModelIndexList selectedIndexes = tableItem->selectionModel()->selectedIndexes();
    bool foundDifferentValue = false;
    for (int i = 0; i < selectedIndexes.size() - 1; i++) {
        QModelIndex index1 = selectedIndexes.at(i);
        QModelIndex index2 = selectedIndexes.at(i + 1);
        int value1 = index1.row();
        int value2 = index2.row();
        if (value1 != value2) {
             foundDifferentValue = true;
             break;
        }
    }
    if (foundDifferentValue){
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error", "Please choose one row!",
                                              QMessageBox::Ok, this);
        msgBox->setStyleSheet("background-color: white;"
                              "font-size: 17px;");

        msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        msgBox->open();
    }
    else if (row >= 0 && isItemSelected == true)
    {
        this->tableItem->removeRow(row);
        manager->listItems.erase(manager->listItems.begin() + row);
        std::fstream file;
        file.open("listItem.txt", std::ios::trunc |std::ios::out);
        if(file.is_open())
        {
            file.seekp(0, std::ios::end);
            for(int i = 0;i < manager->listItems.size(); i++)
            {
                if (file.tellp() == 0)
                {
                    file << manager->listItems[i].getId() << ","
                         << manager->listItems[i].getImage().toStdString() << ","
                         << manager->listItems[i].getName().toStdString() << ","
                         << manager->listItems[i].getPrice().toStdString();
                }
                else
                {
                    file << std::endl << manager->listItems[i].getId() << ","
                                      << manager->listItems[i].getImage().toStdString() << ","
                                      << manager->listItems[i].getName().toStdString() << ","
                                      << manager->listItems[i].getPrice().toStdString();
                }
            }
        }
        file.close();
    }
    else
    {
        if (!isItemSelected)
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error", "Please choose one row before deleting!",
                                                  QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");

            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();
        }
    }
}


void ManagerWindow::on_btn_update_clicked()
{
    int row = this->tableItem->currentRow();
    if (row >= 0 && row < manager->listItems.size())
    {
        QString name = tableItem->item(row, 1)->text();
        QString price = tableItem->item(row, 2)->text();
        QString image = manager->listItems[row].getImage();

        QString new_price = price.replace("VND", "").replace(".","");
        QString nameOld = manager->listItems[row].getName();
        QString priceOld = manager->listItems[row].getPrice();

        QString new_priceOld = priceOld.replace("VND", "").replace(".","");

        if (nameOld == name && new_priceOld == new_price)
        {
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error",
                                                  "You have not edited the data. Please correct data before updating!",
                                                  QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");

            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();
            return;
        }
        else
        {
            manager->listItems[row].setName(name);
            manager->listItems[row].setPrice(new_price);
            manager->listItems[row].setImage(image);

            std::fstream file;
            file.open("listItem.txt", std::ios::trunc |std::ios::out);
            if(file.is_open())
            {
                file.seekp(0, std::ios::end);
                for(int i = 0;i < manager->listItems.size(); i++)
                {
                    if (file.tellp() == 0) {
                        file << manager->listItems[i].getId() << ","
                             << manager->listItems[i].getImage().toStdString() << ","
                             << manager->listItems[i].getName().toStdString() << ","
                             << manager->listItems[i].getPrice().toStdString();
                    }
                    else
                    {
                        file << std::endl << manager->listItems[i].getId() << ","
                                          << manager->listItems[i].getImage().toStdString() << ","
                                          << manager->listItems[i].getName().toStdString() << ","
                                          << manager->listItems[i].getPrice().toStdString();
                    }
                }
            }
            file.close();
            QMessageBox *msgBox = new QMessageBox(QMessageBox::Information, "Update", "Update successfully!",
                                                  QMessageBox::Ok, this);
            msgBox->setStyleSheet("background-color: white;"
                                  "font-size: 17px;");

            msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
            msgBox->open();
        }
    }
    else
    {
        QMessageBox *msgBox = new QMessageBox(QMessageBox::Critical, "Error", "Please enter and save data before updating!",
                                              QMessageBox::Ok, this);
        msgBox->setStyleSheet("background-color: white;"
                              "font-size: 17px;");

        msgBox->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
        msgBox->open();
    }
}



