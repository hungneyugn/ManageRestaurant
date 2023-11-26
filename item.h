#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <QString>


class Item
{
public:
    Item(QString image, QString name,int id, QString price);
    Item(QString name,QString price, QString image);
    void setName(QString name);
    QString getName();
    void setId(int preId,int priority);
    void setId(int id);
    int getId();
    void setPrice(QString price);
    QString getPrice();
    void setImage(QString image);
    QString getImage();
protected:
    QString name;
    int id;
    QString price;
    QString image;
};

#endif // ITEM_H
