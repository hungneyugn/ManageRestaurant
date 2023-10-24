#include "item.h"

Item::Item(QString name,QString price)
{
    this->name = name;
    this->price = price;
    static int id = 100;
    this->id = id;
    id ++;
}
void Item::setName(QString name){
    this->name = name;
}
QString Item::getName(){
    return this->name;
}
int Item::getId(){
    return this->id;
}
void Item::setPrice(QString price){
    this->price = price;
}
QString Item ::getPrice(){
    return this->price;
}
