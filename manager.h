#ifndef MANAGER_H
#define MANAGER_H
#include "manager.h"
#include "vector"
#include "item.h"

class Manager
{
public:
    Manager();
    std::vector<Item>listItems;
    bool checkExistNameItem(QString name);
private:
    int numberOfTable;
    int choiceOption;

};

#endif // MANAGER_H
