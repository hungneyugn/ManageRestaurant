#include "manager.h"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QTextEdit"
#include "QString"
#include "item.h"
#include "QFile"

Manager::Manager()
{
    std::fstream file("listItem.txt", std::ios::in);
    if (file.is_open()) {
        std::string line;
        QString name_1;
        QString price_1;

        while (!file.eof()) {
            std::getline(file, line, '\n');
            std::size_t pos = line.find('-');
            name_1 = QString::fromStdString(line.substr(0, pos));
            price_1 = QString::fromStdString(line.substr(pos + 1));
            if(pos != -1){
                Item newItem(name_1, price_1);
                listItems.push_back(newItem);
            }
        }
        file.close();
    }
}
