#ifndef STAFF_H
#define STAFF_H

#include "table.h"
#include "item.h"
#include "vector"
#include "fstream"
#include "string"
#include "table.h"
#include "algorithm"

class Staff
{
public:
    Staff() = default;
    std::vector<Table *> listTables;
private:
    int numberOfTable;
    std::vector<Item> listItems;
};

#endif // STAFF_H
