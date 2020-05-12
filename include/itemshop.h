#ifndef ITEMSHOP_H
#define ITEMSHOP_H
#include <SFML/Graphics.hpp>
#include "globals.h"

class itemShop
{
public:
    itemShop();
    void setShopPosition (int x, int y);
    void setShopType(int type);
    void drawShop();
    void addItemShop();
    void removeItemShop();
    void interactWithShop(int x, int y, float currenttime);
    int getShopLocationX();
    int getShopLocationY();

private:
    int shopLocationX;
    int shopLocationY;
    int shopBareCoin;
    int shopCommision;
    bool shopIsOpen;
    int shopInventory[10][2]; //item number, amount
    int boxLength = round(viewport_x*0.18);
    int boxHeigth = round(viewport_y*0.4725);
    sf::RectangleShape itemBox;
};

extern itemShop * itemShopList[5];
extern bool addItemShop(itemShop *nItemShop);
extern bool removeItemShop(itemShop *nItemShop);

#endif // ITEMSHOP_H
