#ifndef TABLE_H
#define TABLE_H
#include"vector"
#include "boughtitem.h"
class Table
{
public:
    Table();
    void setStatus(bool status);
    bool getStatus();
    std::vector <BoughtItem>listBookedItem;
private:
    bool status = 0;
};

#endif // TABLE_H
