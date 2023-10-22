#ifndef ITEM_H
#define ITEM_H
#include<string>


class Item
{
public:
    Item(std::string name,std::string price);
    void setName(std::string name);
    std::string getName();
    int getId();
    void setPrice(std::string price);
    std::string getPrice();
protected:
    std::string name;
    int id;
    std::string price;
};

#endif // ITEM_H
