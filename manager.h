#ifndef MANAGER_H
#define MANAGER_H
#include "manager.h"
#include "vector"
#include "string"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QTextEdit"
#include "QString"
#include "item.h"

class Manager
{
public:
    Manager();
    std::vector<Item>listItems;
    bool checkExistNameItem(QString name);
};

#endif // MANAGER_H
