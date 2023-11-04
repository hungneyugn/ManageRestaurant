#include "item.h"

Item::Item(QString name,QString price, QString image)
{
    this->name = name;
    this->price = price;
    this->image = image;
}
void Item::setId(int preId,int priority){
    static int id = preId;
    this->id = id;
    id ++;
}
void Item::setId(int id){
    this->id = id;
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
void Item::setImage(QString image){
    this->image = image;
}
QString Item::getImage(){
    return this->image;
}
