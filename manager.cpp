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

                id = QString::fromStdString(line.substr(0, pos1 - 1));
                image = QString::fromStdString(line.substr(pos1 + 1, pos2 - pos1 - 1));
                name = QString::fromStdString(line.substr(pos2 + 1, pos3 - pos2 - 1));
                price = QString::fromStdString(line.substr(pos3 + 1));

                Item newItem(name, price, image);
                newItem.setId(id.toInt());
                listItems.push_back(newItem);
            }
        }
        file.close();

    }
}
