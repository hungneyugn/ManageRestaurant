#ifndef BOUGHTITEM_H
#define BOUGHTITEM_H

#include "item.h"
#include "QString"

class BoughtItem : public Item
{
public:
    BoughtItem(QString image, QString name, int id, QString price, int quantity);
    void setQuantity(int quantity);
    int getQuantity();

private:
    int quantity;
};

#endif // BOUGHTITEM_H
