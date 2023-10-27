#include "boughtitem.h"
#include "QString"

BoughtItem::BoughtItem(QString name,int id,QString price,int quantity): Item(name,price)
{
    this->name = name;
    this->id = id;
    this->price = price;
    this->quantity = quantity;
}

void BoughtItem::setQuantity(int quantity){
    this->quantity = quantity;
}

int BoughtItem::getQuantity(){
    return this->quantity;
}

