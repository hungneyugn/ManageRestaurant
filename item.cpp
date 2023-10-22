#include "item.h"

Item::Item(std::string name,std::string price)
{
    this->name = name;
    this->price = price;
    static int id = 100;
    this->id = id;
    id ++;
}
void Item::setName(std::string name){
    this->name = name;
}
std::string Item::getName(){
    return this->name;
}
int Item::getId(){
    return this->id;
}
void Item::setPrice(std::string price){
    this->price = price;
}
std::string Item ::getPrice(){
    return this->price;
}
