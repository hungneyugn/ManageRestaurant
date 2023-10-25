#ifndef TABLE_H
#define TABLE_H
#include"vector"
#include "boughtitem.h"
class Table
{
public:
    Table();
    Table(int ordinal, bool status);
    void setStatus(bool status);
    bool getStatus();
    void setOrdinal(int ordinal);
    int getOrdinal();
    std::vector <BoughtItem>listBookedItem;
    std::vector<Table> listTables;
private:
    bool status = 0;
    int ordinal;
};

#endif // TABLE_H
