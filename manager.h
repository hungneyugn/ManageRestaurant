#ifndef MANAGER_H
#define MANAGER_H
#include "manager.h"
#include "vector"
#include "item.h"

class Manager
{
public:
    Manager();
protected:
    int numberOfTable;
    int choiceOption;
    std::vector<Item>listItems;
};

#endif // MANAGER_H
