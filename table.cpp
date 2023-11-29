#include "table.h"

Table::Table()
{
    static int ordinal = 0;
    ordinal = ordinal + 1;
    this->ordinal = ordinal;
    this->status = 0;
}
Table::Table(int ordinal, bool status)
{
    this->ordinal = ordinal;
    this->status=status;
}

void Table::setStatus(bool status){
    this->status = status;
}

bool Table::getStatus()
{
    return this->status;
}

void Table::setOrdinal(int ordinal)
{
    this->ordinal = ordinal;
}

int Table::getOrdinal()
{
    return this->ordinal;
}


