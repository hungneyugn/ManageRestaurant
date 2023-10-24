#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <QString>


class Item
{
public:
    Item(QString name,QString price);
    void setName(QString name);
    QString getName();
    int getId();
    void setPrice(QString price);
    QString getPrice();
protected:
    QString name;
    int id;
    QString price;
};

#endif // ITEM_H
