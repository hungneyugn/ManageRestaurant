#include "manager.h"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QTextEdit"
#include "QString"
#include "item.h"

Manager::Manager()
{
    std::fstream file("listItem.txt", std::ios::in);
    if (file.is_open()) {
        std::string line;
        QString name;
        QString price;
        QString image;
        while (!file.eof()) {
            std::getline(file, line, '\n');
            std::size_t pos = line.find('-');
            name = QString::fromStdString(line.substr(0, pos));
            price = QString::fromStdString(line.substr(pos + 1));
            Item newItem(name, price,image);
            listItems.push_back(newItem);
        }
        file.close();
    }
}
