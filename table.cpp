#include "table.h"

Table::Table()
{
    this->status = 0;
}

void Table::setStatus(bool status){
    this->status = status;
}

bool Table::getStatus()
{
    return this->status;
}
