#include "item.h"

Item::Item(QString image, QString name, int id, QString price)
{
    this->image = image;
    this->name = name;
    this->price = price;
    this->id = id;
}

Item::Item(QString name, QString price, QString image)
{
    this->name = name;
    this->price = price;
    this->image = image;
}

void Item::setId(int preId, int priority)
{
    this->id = preId + 1;
}

void Item::setId(int id)
{
    this->id = id;
}

void Item::setName(QString name)
{
    this->name = name;
}

QString Item::getName()
{
    return this->name;
}

int Item::getId()
{
    return this->id;
}

void Item::setPrice(QString price)
{
    this->price = price;
}

QString Item ::getPrice()
{
    return this->price;
}

void Item::setImage(QString image)
{
    this->image = image;
}

QString Item::getImage()
{
    return this->image;
}
