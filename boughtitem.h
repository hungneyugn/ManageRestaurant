#ifndef BOUGHTITEM_H
#define BOUGHTITEM_H
#include "item.h"

class BoughtItem : public Item
{
public:
    BoughtItem(std::string name,int id,std::string price,int quantity);
    void setQuantity(int quantity);
    int getQuantity();
private:
    int quantity;
};

#endif // BOUGHTITEM_H
