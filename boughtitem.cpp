#include "boughtitem.h"
#include "QString"

BoughtItem::BoughtItem(QString image, QString name,int id,QString price,int quantity): Item(image, name,id,price)
{
    this->quantity = quantity;
}

void BoughtItem::setQuantity(int quantity){
    this->quantity = quantity;
}

int BoughtItem::getQuantity(){
    return this->quantity;
}

