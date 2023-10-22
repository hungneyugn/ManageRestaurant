#include "boughtitem.h"

BoughtItem::BoughtItem(std::string name,int id,std::string price,int quantity): Item(name,price)
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
