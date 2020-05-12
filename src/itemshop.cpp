#include <sstream>
#include "itemshop.h"
#include "gameengine.h"
#include "player.h"
#include "gamemap.h"
#include "soundsystem.h"

itemShop * itemShopList[5];
bool addItemShop(itemShop *nItemShop);
bool removeItemShop(itemShop *nItemShop);

itemShop::itemShop()
{
    this->shopBareCoin = 5000;
    this->shopCommision = 15;
    this->shopIsOpen = true;
    this->shopLocationX = 0;
    this->shopLocationY = 0;
    this->shopInventory[0][0] = 1;
    this->shopInventory[0][1] = 10;
    this->shopInventory[1][0] = 2;
    this->shopInventory[1][1] = 10;
    this->shopInventory[2][0] = 4;
    this->shopInventory[2][1] = 1;
    this->shopInventory[3][0] = 5;
    this->shopInventory[3][1] = 1;
    this->shopInventory[4][0] = 6;
    this->shopInventory[4][1] = 1;
    this->shopInventory[5][0] = 7;
    this->shopInventory[5][1] = 20;
    this->shopInventory[6][0] = 0;
    this->shopInventory[6][1] = 0;
    this->shopInventory[7][0] = 0;
    this->shopInventory[7][1] = 0;
    this->shopInventory[8][0] = 8;
    this->shopInventory[8][1] = 1;
    this->shopInventory[9][0] = 0;
    this->shopInventory[9][1] = 0;
}

void itemShop::setShopPosition (int x, int y)
{
    this->shopLocationX = x;
    this->shopLocationY = y;

}

int itemShop::getShopLocationX()
{
    return this->shopLocationX;
}

int itemShop::getShopLocationY()
{
    return this->shopLocationY;
}

void itemShop::setShopType(int type)
{
    //tbd (de bedoeling is dat dit ooit de inventory en hoeveelheid muntjes en commissie gaat bepalen)
}

void itemShop::drawShop()
{
    Game.sShop.setPosition(this->shopLocationX*32+16, this->shopLocationY*32+16);
    window.draw(Game.sShop);
}

void itemShop::interactWithShop(int x, int y, float currenttime)
{

    if((this->shopLocationX == x ||this->shopLocationX == x-1||this->shopLocationX == x+1) && (this->shopLocationY == y ||this->shopLocationY == y-1||this->shopLocationY == y+1))
    {
        bool actionCompleted = false;
        bool exitShop = false;
        bool sIsPressed = false;
        bool bIsPressed = false;
        int numberIsPressed = -1;
        bool spaceIsPressed = false;
        bool emptySlot = true;
        int startX = viewport_x*0.02;
        int startY = viewport_y*0.01;
        this->itemBox.setSize(sf::Vector2f(this->boxLength, this->boxHeigth));
        this->itemBox.setFillColor(sf::Color(255,255,255,32));
        while(!exitShop)
        {
            window.clear();
            window.setView(totalview);
            window.draw(Game.sGameBackground);
            Game.DrawItemList(this->shopCommision);
            std::stringstream shopGoldStr;
            shopGoldStr << "Shop Gold: " << this->shopBareCoin;
            Game.Gametext(shopGoldStr.str());
            if(!sIsPressed && !bIsPressed)
            {
                if(!actionCompleted)
                {
                    Game.Gametext("Welcome to my shop visitor!");
                    Game.Gametext("What can I do for you?");

                }
                else
                {
                    Game.Gametext("Thank you!");
                    Game.Gametext("Anything else?");
                }
                Game.Gametext("");
                Game.Gametext("Press 'S' to sell an item, 'B' to buy an item and 'Backspace' to return");
                window.setView(view1);
            }
            else if(sIsPressed)
            {
                //de Speler wil iets kopen
                if(numberIsPressed == -1)
                {
                    //De speler heeft nog geen item om te verkopen geselecteerd.
                    Game.Gametext("What would you like to sell?");
                    Game.Gametext("");
                    Game.Gametext("Please, press the number of the item in your inventory. ");
                    Game.Gametext("To return press 'R'.");
                }
                else
                {
                    //De speler heeft een item om te verkopen geselecteerd, vraag hem wat hij wil verkopen
                    if(spaceIsPressed)
                    {
                        //de speler weet het zeker, voer de transactie uit
                        int itemPrice1;
                        itemPrice1 = round( Game.itemPriceList[Player.nInventory[numberIsPressed]])* (1-(this->shopCommision/100.00)) ;
                        if(this->shopBareCoin >= itemPrice1)
                        {
                            bool itemSlotShopUsed = false;
                            for(int i = 0; i < 10; i++)
                            {
                                if(shopInventory[i][0] == Player.nInventory[numberIsPressed] && !itemSlotShopUsed)
                                {
                                    Player.aInventory[numberIsPressed] = Player.aInventory[numberIsPressed] - 1;
                                    shopInventory[i][1]++;
                                    if(Player.aInventory[numberIsPressed] == 0)
                                    {
                                        Player.attack =  Player.attack - current_map.nItemDMG[Player.nInventory[numberIsPressed]];
                                        Player.armor = Player.armor - current_map.nItemARM[Player.nInventory[numberIsPressed]];
                                        Player.nInventory[numberIsPressed] = 0;
                                    }
                                    itemSlotShopUsed = true;
                                }
                            }
                            for(int i = 0; i < 10; i++)
                            {
                                if(shopInventory[i][0] == 0 && !itemSlotShopUsed)
                                {
                                    Player.aInventory[i] = Player.aInventory[i] - 1;
                                    if(Player.aInventory[i] == 0)
                                    {
                                        Player.attack =  Player.attack - current_map.nItemDMG[Player.nInventory[i]];
                                        Player.armor = Player.armor - current_map.nItemARM[Player.nInventory[i]];
                                        shopInventory[i][0] = Player.nInventory[i];
                                        shopInventory[i][1] = 1;
                                        Player.nInventory[i] = 0;
                                    }
                                    itemSlotShopUsed = true;
                                }
                            }
                            if(!itemSlotShopUsed)
                            {
                                //De winkel heeft geen plek!
                                Game.Gametext("Sorry I do not have space for this item.");
                                Game.Gametext("");
                                Game.Gametext("");
                                Game.Gametext("To return press 'R'.");
                            }
                            else
                            {
                                this->shopBareCoin = this->shopBareCoin - itemPrice1;
                                Player.Gold = Player.Gold + itemPrice1;
                                actionCompleted = true;
                                sIsPressed = false;
                                bIsPressed = false;
                                numberIsPressed = -1;
                                spaceIsPressed = false;
                                emptySlot = true;
                            }
                        }
                        else
                        {
                            Game.Gametext("Sorry I do not have the gold for this item.");
                            Game.Gametext("");
                            Game.Gametext("");
                            Game.Gametext("To return press 'R'.");
                        }
                    }
                    else if(Player.nInventory[numberIsPressed] == 0)
                    {
                        //Er zit geen item in dit slot
                        emptySlot = true;
                        Game.Gametext("Sorry, but there is nothing in that item slot!");
                        Game.Gametext("What would you like to sell?");
                        Game.Gametext("Please, press the number of the item in your inventory. ");
                        Game.Gametext("To return press 'R'.");
                    }
                    else
                    {
                        //Vraag de speler of hij het zeker weet
                        emptySlot = false;
                        std::stringstream shopTextString;
                        shopTextString << "So you would like to sell: " << Game.itemNameList[Player.nInventory[numberIsPressed]] <<"?";
                        Game.Gametext(shopTextString.str());
                        Game.Gametext("");
                        Game.Gametext("");
                        Game.Gametext("Please, press 'Spacebar' to confirm the transaction or 'N' to cancel");
                    }

                }
            }
            else
            {
                //b is blijkbaar ingedrukt dus de speler wil iets kopen
                if(numberIsPressed == -1 || shopInventory[numberIsPressed][0] == 0)
                {
                    //De speler heeft nog geen item om te kopen geselecteerd, vraag hem wat hij wil kopen.
                    if(shopInventory[numberIsPressed][0] == 0)
                    {
                        emptySlot = true;
                        numberIsPressed = -1;
                    }
                    Game.Gametext("What would you like to buy?");
                    Game.Gametext("");
                    Game.Gametext("Please, press the number of the item in the shop.");
                    Game.Gametext("To return press 'R'.");

                }
                else
                {
                    //De speler heeft een item om te kopen geselecteerd
                    if(spaceIsPressed)
                    {
                        //de speler weet het zeker, voer de transactie uit, maar check eerst of de speler het kan betalen
                        int itemPrice1;
                        itemPrice1 = round( Game.itemPriceList[shopInventory[numberIsPressed][0]])* (1+(this->shopCommision/100.00)) ;
                        if(Player.Gold >=  itemPrice1)
                        {
                            //add item
                            int exist = 0;
                            bool itemPlaced = false;
                            for( int i = 0; i < 10; i++ )
                            {
                                if(Player.nInventory[i] == shopInventory[numberIsPressed][0] && !itemPlaced)
                                {
                                    exist = 1;
                                    Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
                                    Audio.sound4.setBuffer(Audio.sbuffer4);
                                    Audio.sound4.play();
                                    Player.aInventory[i] = Player.aInventory[i] + 1;
                                    itemPlaced = true;
                                }
                            }
                            if(exist == 0)
                            {
                                for( int i = 0; i < 10; i++ )
                                {
                                    if(Player.nInventory[i] == 0 && !itemPlaced)
                                    {
                                        Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
                                        Audio.sound4.setBuffer(Audio.sbuffer4);
                                        Audio.sound4.play();
                                        Player.armor = Player.armor + current_map.nItemARM[shopInventory[numberIsPressed][0]];
                                        Player.attack = Player.attack + current_map.nItemDMG[shopInventory[numberIsPressed][0]];
                                        Player.nInventory[i] = shopInventory[numberIsPressed][0]; //item
                                        Player.aInventory[i] = 1;
                                        itemPlaced = true;
                                    }
                                }
                            }
                            if(!itemPlaced)
                            {
                                //Er was geen vrij slot!
                                Game.Gametext("Sorry you do not have space for this item.");
                                Game.Gametext("");
                                Game.Gametext("");
                                Game.Gametext("To return press 'R'.");
                            }
                            else
                            {
                                this->shopBareCoin = this->shopBareCoin + itemPrice1;
                                Player.Gold = Player.Gold - itemPrice1;
                                actionCompleted = true;
                                sIsPressed = false;
                                bIsPressed = false;
                                numberIsPressed = -1;
                                spaceIsPressed = false;
                                emptySlot = true;
                            }
                        }
                        else
                        {
                            // de speler heeft te weinig goud
                            Game.Gametext("Sorry you do not have enough gold to pay.");
                            Game.Gametext("");
                            Game.Gametext("");
                            Game.Gametext("To return press 'R'.");
                        }
                    }
                    else
                    {
                        //Vraag de speler of hij het zeker weet
                        std::stringstream shopTextString;
                        emptySlot = false;
                        shopTextString << "So you would like to buy: " << Game.itemNameList[shopInventory[numberIsPressed][0]] <<"?";
                        Game.Gametext(shopTextString.str());
                        Game.Gametext("");
                        Game.Gametext("");
                        Game.Gametext("Please, press 'Spacebar' to confirm the transaction or 'N' to cancel");
                    }

                }
            }


            //hier komen shop dingen
            window.setView(totalview);
            sf::Font font;
            sf::Text text;
            if (!font.loadFromFile("fonts/TrajanPro-Regular.otf"))
            {
                // error...
            }
            text.setFont(font);
            text.setCharacterSize(item_list_y);
            text.setColor(sf::Color::White);
            text.setOutlineColor(sf::Color::Black);
            int itemNumber = 0;
            int nY = 0;
            while(nY < 2)
            {
                int nX = 0;
                while(nX < 5)
                {
                    int offsetX = (this->boxLength + (viewport_x*0.015))* nX;
                    int offsetY = (this->boxHeigth + (viewport_y*0.025))* nY;
                    this->itemBox.setPosition(startX+offsetX, startY+offsetY);
                    window.draw(this->itemBox);
                    std::stringstream headerText;
                    headerText << "Slot number: " << itemNumber;
                    text.setString(headerText.str());
                    text.setPosition(startX+offsetX+20, startY+offsetY+20);
                    window.draw(text);
                    text.setPosition(startX+offsetX+20, startY+offsetY+22+(item_list_y*2));
                    text.setString("Item on sale: ");
                    window.draw(text);
                    text.setPosition(startX+offsetX+20, startY+offsetY+22+(item_list_y*3));
                    text.setString(Game.itemNameList[shopInventory[itemNumber][0]]);
                    window.draw(text);
                    text.setPosition(startX+offsetX+20, startY+offsetY+22+(item_list_y*5));
                    text.setString("Price: ");
                    window.draw(text);
                    text.setPosition(startX+offsetX+20, startY+offsetY+22+(item_list_y*6));
                    int itemPrice;
                    itemPrice = round( Game.itemPriceList[shopInventory[itemNumber][0]])* (1+(this->shopCommision/100.00)) ;
                    std::stringstream itemPriceString;
                    itemPriceString << itemPrice;
                    text.setString(itemPriceString.str());
                    window.draw(text);
                    text.setPosition(startX+offsetX+20, startY+offsetY+22+(item_list_y*8));
                    text.setString("Amount available: ");
                    window.draw(text);
                    text.setPosition(startX+offsetX+20, startY+offsetY+22+(item_list_y*9));
                    std::stringstream itemAmountString;
                    itemAmountString << shopInventory[itemNumber][1];
                    text.setString(itemAmountString.str());
                    window.draw(text);
                    switch (shopInventory[itemNumber][0])
                    {
                    case 0:
                        break;
                    case 1:
                        Game.sItem_PotionShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_PotionShop);
                        break;
                    case 2:
                        Game.sItem_RockShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_RockShop);
                        break;
                    case 3:
                        Game.sItem_KeyShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_KeyShop);
                        break;
                    case 4:
                        Game.sItem_PickaxeShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_PickaxeShop);
                        break;
                    case 5:
                        Game.sItem_WoodenSwordShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_WoodenSwordShop);
                        break;
                    case 6:
                        Game.sItem_BowShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_BowShop);
                        break;
                    case 7:
                        Game.sItem_ArrowShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_ArrowShop);
                        break;
                    case 8:
                        Game.sItem_ShieldShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_ShieldShop);
                        break;
                    case 9:
                        Game.sItem_ShipShop.setPosition(startX+offsetX+20, startY+offsetY+30+(item_list_y*11));
                        window.draw(Game.sItem_ShipShop);
                        break;
                    }
                    itemNumber++;
                    nX++;
                }
                nY++;
            }


            window.display();
            Game.gametext = 0;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
            {
                exitShop = true;
                window.clear();
                window.setView(totalview);
                window.draw(Game.sGameBackground);
                Game.DrawItemList(0);
                Game.Gametext("Thanks for shopping!");
                Game.Gametext("");
                Game.Gametext("");
                Game.Gametext("Press 'Enter' to continue... ");
                window.setView(view1);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                sIsPressed = true;
                spaceIsPressed = false;
                numberIsPressed = -1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            {
                bIsPressed = true;
                spaceIsPressed = false;
                numberIsPressed = -1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                bIsPressed = false;
                sIsPressed = false;
                numberIsPressed = -1;
                emptySlot = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                spaceIsPressed = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) && emptySlot)
            {
                numberIsPressed = 0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && emptySlot)
            {
                numberIsPressed = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && emptySlot)
            {
                numberIsPressed = 2;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && emptySlot)
            {
                numberIsPressed = 3;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && emptySlot)
            {
                numberIsPressed = 4;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && emptySlot)
            {
                numberIsPressed = 5;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && emptySlot)
            {
                numberIsPressed = 6;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && emptySlot)
            {
                numberIsPressed = 7;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && emptySlot)
            {
                numberIsPressed = 8;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && emptySlot)
            {
                numberIsPressed = 9;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            {
                numberIsPressed = -1;
                emptySlot = true;
            }
        }
    }
}

bool addItemShop(itemShop *nItemShop)
{
    for(int i = 0; i < 5; i++)
    {
        if(itemShopList[i] == NULL)
        {
            itemShopList[i] = nItemShop;
            return true;
        }
    }
    return false;
}

bool removeItemShop(itemShop *nItemShop)
{
    for(int i = 0; i < 5; i++)
    {
        if(itemShopList[i] == nItemShop)
        {
            delete nItemShop;
            itemShopList[i] = NULL;
            return true;
        }
    }
    return false;
}
