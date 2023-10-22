#ifndef STAFF_H
#define STAFF_H
#include "vector"
#include "table.h"
#include "item.h"
class Staff
{
public:
    Staff();
private:
    int numberOfTable;
    /*variable save numbers of table which was chosen*/
    int currentTable;
    /*list of tables was generated with the number of table*/
    std::vector<Table> listTables;
    std::vector<Item> listItems;
    int choiceMenu;
};

#endif // STAFF_H
