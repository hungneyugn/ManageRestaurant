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
            std::size_t pos1 = line.find('-');
            std::size_t pos2 = line.find('-', pos1 + 1);
            name = QString::fromStdString(line.substr(0, pos1));
            price = QString::fromStdString(line.substr(pos1 + 1, pos2 - pos1 - 1));
            image = QString::fromStdString(line.substr(pos2 + 1));
            Item newItem(name, price,image);
            listItems.push_back(newItem);
        }
        file.close();
    }
}
