#include "player.h"
#include "gameengine.h"
#include "gamemap.h"
#include "soundsystem.h"
#include "actors.h"
#include "npc.h"
#include "itemshop.h"

Player_State Player;

void Player_State::OrientPlayer( float timepressed_x, float timepressed_y, float timepressed_up, float timepressed_down, float timepressed_left, float timepressed_right, float currentTime)
{
    bool schuin = false;
    int orient_y = 0;
    int orient_x = 0;
    if(timepressed_x-timepressed_y < 0.3 && timepressed_x-timepressed_y >= 0 && timepressed_x +0.3 > currentTime)
    {
        //beide knoppen zijn kort na elkaar ingedrukt en de animatie is nog bezig.
        schuin = true;
    }
    else if(timepressed_y-timepressed_x < 0.3 && timepressed_y-timepressed_x >= 0 && timepressed_y +0.3 > currentTime)
    {
        //beide knoppen zijn kort na elkaar ingedrukt en de animatie is nog bezig.
        schuin = true;
    }
    else
    {
        schuin = false;
    }
    if(schuin == true)
    {
        if(timepressed_up > timepressed_down)
        {
            orient_y = 1;
        }
        else
        {
            orient_y = 0;
        }
        if(timepressed_left > timepressed_right)
        {
            orient_x = 1;
        }
        else
        {
            orient_x = 0;
        }
        if(orient_y == 1 && orient_x == 1)
        {
            //  ^<
            Game.splayer.setRotation(315);
        }
        else if (orient_y == 1 && orient_x == 0)
        {
            // ^>
            Game.splayer.setRotation(45);
        }
        else if (orient_y == 0 && orient_x == 1)
        {
            //v<
            Game.splayer.setRotation(225);
        }
        else if (orient_y == 0 && orient_x == 0)
        {
            //v>
            Game.splayer.setRotation(135);
        }
    }
    else
    {
        if(timepressed_up > timepressed_down)
        {
            orient_y = 1;
        }
        else
        {
            orient_y = 0;
        }
        if(timepressed_left > timepressed_right)
        {
            orient_x = 1;
        }
        else
        {
            orient_x = 0;
        }
        if(timepressed_y > timepressed_x)
        {
            if(orient_y == 1)
            {
                //^
                Game.splayer.setRotation(0); //up
            }
            else
            {
                //v
                Game.splayer.setRotation(180); //down
            }
        }
        else
        {
            if(orient_x == 1)
            {
                //<
                Game.splayer.setRotation(270); //left
            }
            else
            {
                //>
                Game.splayer.setRotation(90); //right
            }
        }
    }
}

void Player_State::Level_up()
{
    int experience_needed = pow(5, Lvl);
    if(Experience >= experience_needed)
    {
        Lvl = Lvl + 1;
        max_health = 100 + (5 *(Lvl-1));
        max_mana = 100 + (5 *(Lvl-1));
    }
}
bool Player_State::boardShip(bool inBoat)
{
    int nposition_x = Player.position_x;
    int nposition_y = Player.position_y;
    switch (porientation)
    {
    case 1:
        nposition_y = nposition_y - 1;
        break;
    case 2:
        nposition_y = nposition_y + 1;
        break;
    case 3:
        nposition_x = nposition_x + 1;
        break;
    case 4:
        nposition_x = nposition_x - 1;
        break;
    }
    if(inBoat == false)
    {
        //Speler wil de boot die voor hem is in.
        if(current_map.nItemArray[nposition_y][nposition_x] == 9)
        {
            current_map.nOccupied[Player.position_y][Player.position_x] = 0;
            //Oke er is een boot voor de speler! Hij mag erin.
            Player.position_x = nposition_x;
            Player.position_y = nposition_y;
            current_map.nItemArray[Player.position_y][Player.position_x] = 0;
            current_map.nOccupied[Player.position_y][Player.position_x] = 1;
            Game.splayer.setTexture(Game.playerInBoat);
            return true;
        }
        else
        {
            //Geen boot
            return false;
        }
    }
    else
    {
        //Speler wil de boot uit.
        if(current_map.ispassable(nposition_x, nposition_y, false, false))
        {
            //Oke het is land
            current_map.nOccupied[Player.position_y][Player.position_x] = 0;
            current_map.nItemArray[Player.position_y][Player.position_x] = 9;
            Player.position_x = nposition_x;
            Player.position_y = nposition_y;
            current_map.nOccupied[Player.position_y][Player.position_x] = 1;
            Game.splayer.setTexture(Game.tplayerUp);
            return false;
        }
        else
        {
            // whoops het is water of niet passeerbaar
            return true;
        }
    }
}
void Player_State::DrawPlayer(int change_x, int change_y, float timepressed, float currentTime)
{
    float hbx = (health/max_health)*32;
    float mbx = (mana/max_mana)*32;
    sf::RectangleShape health_bar_front;
    sf::RectangleShape health_bar_background;
    sf::RectangleShape mana_bar_front;
    sf::RectangleShape mana_bar_background;
    health_bar_background.setSize(sf::Vector2f( 32, 2 ));
    health_bar_front.setSize(sf::Vector2f(hbx, 2 ));
    health_bar_background.setOutlineThickness(1);
    health_bar_background.setOutlineColor(sf::Color::Black);
    health_bar_background.setFillColor(sf::Color::Red);
    health_bar_front.setFillColor(sf::Color::Green);
    mana_bar_background.setSize(sf::Vector2f( 32, 2 ));
    mana_bar_front.setSize(sf::Vector2f(mbx, 2 ));
    mana_bar_background.setOutlineThickness(1);
    mana_bar_background.setOutlineColor(sf::Color::Black);
    mana_bar_background.setFillColor(sf::Color::Blue);
    mana_bar_front.setFillColor(sf::Color::Cyan);
    float tempx, tempy;
    if(timepressed + 0.3 > currentTime)
    {
        switch (change_x)
        {
        case -1:
            tempx = position_x + 1 - (1*((currentTime-timepressed)/0.3));
            break;
        case 0:
            tempx = position_x;
            break;
        case 1:
            tempx = position_x -1 + (1*((currentTime-timepressed)/0.3));
            break;
        }

        switch (change_y)
        {
        case -1:
            tempy = position_y + 1 - (1*((currentTime-timepressed)/0.3));
            break;
        case 0:
            tempy = position_y;
            break;
        case 1:
            tempy = position_y - 1 + (1*((currentTime-timepressed)/0.3));
            break;
        }
        int tempx1 = tempx *32+16;
        int tempy1 = tempy *32+16;
        Game.splayer.setPosition(tempx1, tempy1);
        health_bar_background.setPosition(tempx*32, tempy*32+34);
        health_bar_front.setPosition(tempx*32, tempy*32+34);
        mana_bar_background.setPosition(tempx*32, tempy*32+40);
        mana_bar_front.setPosition(tempx*32, tempy*32+40);
    }
    else
    {
        Game.splayer.setPosition(position_x*32+16, position_y*32+16);
        health_bar_background.setPosition(position_x*32, position_y*32+34);
        health_bar_front.setPosition(position_x*32, position_y*32+34);
        mana_bar_background.setPosition(position_x*32, position_y*32+40);
        mana_bar_front.setPosition(position_x*32, position_y*32+40);
    }
    window.draw(Game.splayer);
    window.draw(health_bar_background);
    window.draw(health_bar_front);
    window.draw(mana_bar_background);
    window.draw(mana_bar_front);
}

void Player_State::DropItem()
{
    window.setView(totalview);
    window.draw(Game.sGameBackground);
    Game.Gametext("Which Item do you want to drop? To cancel press Backspace.");
    Game.gametext = 0;
    window.setView(view1);
    current_map.DrawMap();
    current_map.DrawItems();
    DrawPlayer(0,0,0,0);
    window.setView(totalview);
    Game.DrawItemList(0);
    window.display();
    int i = -1;
    while(i == -1)
    {
        while (window.pollEvent(Game.event))
        {
            switch(Game.event.type)
            {
            case sf::Event::KeyPressed:
                switch(Game.event.key.code)
                {
                case sf::Keyboard::Num0:
                    i = 0;
                    break;
                case sf::Keyboard::Num1:
                    i = 1;
                    break;
                case sf::Keyboard::Num2:
                    i = 2;
                    break;
                case sf::Keyboard::Num3:
                    i = 3;
                    break;
                case sf::Keyboard::Num4:
                    i = 4;
                    break;
                case sf::Keyboard::Num5:
                    i = 5;
                    break;
                case sf::Keyboard::Num6:
                    i = 6;
                    break;
                case sf::Keyboard::Num7:
                    i = 7;
                    break;
                case sf::Keyboard::Num8:
                    i = 8;
                    break;
                case sf::Keyboard::Num9:
                    i = 9;
                    break;
                case sf::Keyboard::Backspace:
                    i = 10;
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }
    if(i == 10)
    {
        return;
    }
    else
    {
        if(current_map.nItemArray[position_y][position_x] == 0)
        {
            //alles oke
            current_map.nItemArray[Player.position_y][Player.position_x] = Player.nInventory[i];
            Player.aInventory[i] = Player.aInventory[i] - 1;
            if(Player.aInventory[i] == 0)
            {
                Player.attack =  Player.attack - current_map.nItemDMG[nInventory[i]];
                Player.armor = Player.armor - current_map.nItemARM[nInventory[i]];
                Player.nInventory[i] = 0;
            }
        }
        else
        {
            window.clear();
            window.setView(totalview);
            window.draw(Game.sGameBackground);
            Game.Gametext("There is no place to drop the item!");
            Game.gametext = 0;
            window.setView(view1);
            current_map.DrawMap();
            current_map.DrawItems();
            DrawPlayer(0,0,0,0);
            window.setView(totalview);
            Game.DrawItemList(0);
            window.display();
            while(i!= -1)
            {
                while (window.pollEvent(Game.event))
                {
                    switch(Game.event.type)
                    {
                    case sf::Event::KeyPressed:
                        switch(Game.event.key.code)
                        {
                        case sf::Keyboard::Return:
                            i = -1;
                            break;
                        case sf::Keyboard::Backspace:
                            i = -1;
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Player_State::UseItem()
{
    int nposition_x = Player.position_x;
    int nposition_y = Player.position_y;
    window.setView(totalview);
    window.draw(Game.sGameBackground);
    Game.Gametext("Which Item do you want to use? To cancel press 'Backspace'.");
    Game.gametext = 0;
    window.setView(view1);
    current_map.DrawMap();
    current_map.DrawItems();
    DrawPlayer(0,0,0,0);
    window.setView(totalview);
    Game.DrawItemList(0);
    window.display();
    int i = -1;
    while(i == -1)
    {
        while (window.pollEvent(Game.event))
        {
            switch(Game.event.type)
            {
            case sf::Event::KeyPressed:
                switch(Game.event.key.code)
                {
                case sf::Keyboard::Num0:
                    i = 0;
                    break;
                case sf::Keyboard::Num1:
                    i = 1;
                    break;
                case sf::Keyboard::Num2:
                    i = 2;
                    break;
                case sf::Keyboard::Num3:
                    i = 3;
                    break;
                case sf::Keyboard::Num4:
                    i = 4;
                    break;
                case sf::Keyboard::Num5:
                    i = 5;
                    break;
                case sf::Keyboard::Num6:
                    i = 6;
                    break;
                case sf::Keyboard::Num7:
                    i = 7;
                    break;
                case sf::Keyboard::Num8:
                    i = 8;
                    break;
                case sf::Keyboard::Num9:
                    i = 9;
                    break;
                case sf::Keyboard::Backspace:
                    i = 10;
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }
    if(i == 10)
    {
        return;
    }
    else
    {
        if(nInventory[i] != 0)
        {
            window.clear();
            window.setView(totalview);
            window.draw(Game.sGameBackground);
            switch(nInventory[i])
            {
            case 1:
                Game.Gametext("Are you sure you want to your Potion? Yes = Enter; No = Backspace");
                break;
            case 2:
                Game.Gametext("Are you sure you want to use your Rock? Yes = Enter; No = Backspace");
                break;
            case 3:
                Game.Gametext("Are you sure you want to use your Key? Yes = Enter; No = Backspace");
                break;
            case 4:
                Game.Gametext("Are you sure you want to use Pickaxe? Yes = Enter; No = Backspace");
                break;
            case 10:
                Game.Gametext("Are you sure you want to use 'Mana Potion'? Yes = Enter; No = Backspace");
                break;
            default:
                Game.Gametext("This item can't be used in this way!");
                break;
            }
            Game.gametext = 0;
            window.setView(view1);
            current_map.DrawMap();
            current_map.DrawItems();
            DrawPlayer(0,0,0,0);
            window.setView(totalview);
            Game.DrawItemList(0);
            window.display();
            int e = 0;
            while(e!= 12 && e != 13)
            {
                while (window.pollEvent(Game.event))
                {
                    switch(Game.event.type)
                    {
                    case sf::Event::KeyPressed:
                        switch(Game.event.key.code)
                        {
                        case sf::Keyboard::Return:
                            e = 12;
                            break;
                        case sf::Keyboard::Backspace:
                            e = 13;
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                }
            }
            if(e == 12)
            {
                //item wordt gebruikt
                window.clear();
                window.setView(totalview);
                window.draw(Game.sGameBackground);
                switch (porientation)
                {
                case 1:
                    nposition_y = nposition_y - 1;
                    break;
                case 2:
                    nposition_y = nposition_y + 1;
                    break;
                case 3:
                    nposition_x = nposition_x + 1;
                    break;
                case 4:
                    nposition_x = nposition_x - 1;
                    break;
                }
                switch(nInventory[i])
                {
                case 1:
                    Game.Gametext("You drank your Potion! *Burp!* Press Enter to continue...");
                    Player.armor = Player.armor - current_map.nItemARM[1];
                    Audio.sbuffer3.loadFromFile("audio/power up.wav");
                    Audio.sound3.setBuffer(Audio.sbuffer3);
                    Audio.sound3.play();
                    Player.aInventory[i] = Player.aInventory[i] - 1;
                    if(Player.aInventory[i] == 0)
                    {
                        Player.nInventory[i] = 0;
                    }
                    Player.health = Player.health + 75;
                    if(Player.health > max_health)
                    {
                        Player.health = max_health;
                    }
                    break;
                case 2:
                    Game.Gametext("You threw your Rock! Look at it go! Press Enter to continue...");
                    Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
                    Audio.sound4.setBuffer(Audio.sbuffer4);
                    Audio.sound4.play();
                    if(current_map.ispassable(nposition_x,nposition_y, false, false))
                    {
                        current_map.nItemArray[nposition_y][nposition_x] = 2;
                        aInventory[i] = aInventory[i] - 1;
                        if(aInventory[i] == 0)
                        {
                            nInventory[i] = 0;
                            Player.attack =  Player.attack - current_map.nItemDMG[2];
                            Player.armor = Player.armor - current_map.nItemARM[2];
                        }
                    }
                    else
                    {
                        current_map.nItemArray[position_y][position_x] = 2;
                        aInventory[i] = aInventory[i] - 1;
                        if(aInventory[i] == 0)
                        {
                            nInventory[i] = 0;
                        }
                    }
                    break;
                case 3:
                    if(current_map.nMapArray[nposition_y][nposition_x] == 6)
                    {
                        Game.Gametext("You unlocked the door. What secrets will you uncover? Press Enter");
                        Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
                        Audio.sound4.setBuffer(Audio.sbuffer4);
                        Audio.sound4.play();
                        current_map.nMapArray[nposition_y][nposition_x] = 2;
                        aInventory[i] = aInventory[i] - 1;
                        if(aInventory[i] == 0)
                        {
                            nInventory[i] = 0;
                        }
                    }
                    else
                    {
                        Game.Gametext("You can only use your key when you face a door! Press Enter to continue...");
                    }
                    break;
                case 4:
                    if(current_map.nMapArray[nposition_y][nposition_x] == 1)
                    {
                        current_map.nMapArray[nposition_y][nposition_x] = 0;
                        if(current_map.nItemArray[nposition_y][nposition_x] == 0)
                        {
                            current_map.nItemArray[nposition_y][nposition_x] = 2;
                        }
                        aInventory[i] = aInventory[i] - 1;
                        if(aInventory[i] == 0)
                        {
                            Player.attack =  Player.attack - current_map.nItemDMG[4];
                            Player.armor = Player.armor - current_map.nItemARM[4];
                            nInventory[i] = 0;
                        }
                        Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
                        Audio.sound4.setBuffer(Audio.sbuffer4);
                        Audio.sound4.play();
                    }
                    Game.Gametext("Chop, Chop, Chop! Press Enter to continue...");
                    break;
                case 10:
                    Game.Gametext("You drank your Mana Potion! *Ahh!* Press Enter to continue...");
                    Player.armor = Player.armor - current_map.nItemARM[1];
                    Audio.sbuffer3.loadFromFile("audio/power up.wav");
                    Audio.sound3.setBuffer(Audio.sbuffer3);
                    Audio.sound3.play();
                    Player.aInventory[i] = Player.aInventory[i] - 1;
                    if(Player.aInventory[i] == 0)
                    {
                        Player.nInventory[i] = 0;
                    }
                    Player.mana = Player.mana + 75;
                    if(Player.mana > max_mana)
                    {
                        Player.mana = max_mana;
                    }
                    break;
                }
                Game.gametext = 0;
                window.setView(view1);
                current_map.DrawMap();
                current_map.DrawItems();
                DrawPlayer(0,0,0,0);
                window.setView(totalview);
                Game.DrawItemList(0);
                window.display();
                i = 1;
                while(i != 0)
                {
                    while (window.pollEvent(Game.event))
                    {
                        switch(Game.event.type)
                        {
                        case sf::Event::KeyPressed:
                            switch(Game.event.key.code)
                            {
                            case sf::Keyboard::Return:
                                i = 0;
                                break;
                            case sf::Keyboard::Backspace:
                                i = 0;
                                break;
                            default:
                                break;
                            }
                            break;
                        }
                    }
                }
            }
            else
            {
                return;
            }
        }
        else
        {
            window.clear();
            window.setView(totalview);
            window.draw(Game.sGameBackground);
            Game.Gametext("There is no item in this slot! Press Enter to continue.");
            Audio.sbuffer6.loadFromFile("audio/Error.wav");
            Audio.sound6.setBuffer(Audio.sbuffer6);
            Audio.sound6.play();
            Game.gametext = 0;
            window.setView(view1);
            current_map.DrawMap();
            current_map.DrawItems();
            DrawPlayer(0,0,0,0);
            window.setView(totalview);
            Game.DrawItemList(0);
            window.display();
            while(i!= -1)
            {
                while (window.pollEvent(Game.event))
                {
                    switch(Game.event.type)
                    {
                    case sf::Event::KeyPressed:
                        switch(Game.event.key.code)
                        {
                        case sf::Keyboard::Return:
                            i = -1;
                            break;
                        case sf::Keyboard::Backspace:
                            i = -1;
                            break;
                        default:
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Player_State::UseDoor()
{
    int nposition_x = position_x;
    int nposition_y = position_y;
    window.setView(totalview);
    window.draw(Game.sGameBackground);
    switch (porientation)
    {
    case 1:
        nposition_y = nposition_y - 1;
        break;
    case 2:
        nposition_y = nposition_y + 1;
        break;
    case 3:
        nposition_x = nposition_x + 1;
        break;
    case 4:
        nposition_x = nposition_x - 1;
        break;
    }
    if(current_map.nMapArray[nposition_y][nposition_x] == 2)
    {
        Game.Gametext("You opened the door! Press Enter to continue.");
        Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
        Audio.sound4.setBuffer(Audio.sbuffer4);
        Audio.sound4.play();
        current_map.nMapArray[nposition_y][nposition_x] = 3;
    }
    else if(current_map.nMapArray[nposition_y][nposition_x] == 3)
    {
        Game.Gametext("You closed the door! Press Enter to continue.");
        Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
        Audio.sound4.setBuffer(Audio.sbuffer4);
        Audio.sound4.play();
        current_map.nMapArray[nposition_y][nposition_x] = 2;
    }
    else if(current_map.nMapArray[nposition_y][nposition_x] == 6)
    {
        Game.Gametext("This door is locked! Press Enter to continue.");
        Audio.sbuffer6.loadFromFile("audio/Error.wav");
        Audio.sound6.setBuffer(Audio.sbuffer6);
        Audio.sound6.play();
    }
    else
    {
        Game.Gametext("There is no door! Press Enter to continue.");
        Audio.sbuffer6.loadFromFile("audio/Error.wav");
        Audio.sound6.setBuffer(Audio.sbuffer6);
        Audio.sound6.play();
    }
    Game.gametext = 0;
    window.setView(view1);
    current_map.DrawMap();
    current_map.DrawItems();
    DrawPlayer(0,0,0,0);
    window.setView(totalview);
    Game.DrawItemList(0);
    window.display();
    int i = 0;
    while(i == 0)
    {
        while (window.pollEvent(Game.event))
        {
            switch(Game.event.type)
            {
            case sf::Event::KeyPressed:
                switch(Game.event.key.code)
                {
                case sf::Keyboard::Return:
                    i = 1;
                    break;
                case sf::Keyboard::Backspace:
                    i = 1;
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }
}

void Player_State::Do_Attack()
{
    Audio.sbuffer.loadFromFile("audio/schiet 1.wav");
    Audio.sound.setBuffer(Audio.sbuffer);
    Audio.sound.play();
    for(int i = 0; i < MAX_ACTORS; i++ )
    {
        if(p_cActorList[i] != NULL )
        {
            int attack_X = Player.position_x;
            int attack_Y = Player.position_y;
            switch (Player.porientation)
            {
            case 1:
                attack_Y = attack_Y - 1;
                break;
            case 2:
                attack_Y = attack_Y + 1;
                break;
            case 3:
                attack_X = attack_X + 1;
                break;
            case 4:
                attack_X = attack_X - 1;
                break;
            }
            if(p_cActorList[i]->TakeDamage(attack_X, attack_Y, Player.attack))
            {
                Audio.sbuffer2.loadFromFile("audio/Damage 1.wav");
                Audio.sound2.setBuffer(Audio.sbuffer2);
                Audio.sound2.play();
                RemoveActorFromList(p_cActorList[i]);
                Experience = Experience + 1;
                current_map.nOccupied[attack_Y][attack_X] = 0;
                Player.Gold = Player.Gold + 10;
                Game.current_actors = Game.current_actors -1;
            }
        }
    }
}

void Player_State::Do_Magic_Attack()
{
    Player.mana = Player.mana - 10;
    Audio.sbuffer.loadFromFile("audio/schiet 1.wav");
    Audio.sound.setBuffer(Audio.sbuffer);
    Audio.sound.play();
    for(int i = 0; i < MAX_ACTORS; i++ )
    {
        if(p_cActorList[i] != NULL )
        {
            int attack_X = Player.position_x;
            int attack_Y = Player.position_y;
            switch (Player.porientation)
            {
            case 1:
                attack_Y = attack_Y - 1;
                break;
            case 2:
                attack_Y = attack_Y + 1;
                break;
            case 3:
                attack_X = attack_X + 1;
                break;
            case 4:
                attack_X = attack_X - 1;
                break;
            }

            if(p_cActorList[i]->TakeDamage(attack_X, attack_Y, Player.magic_attack))
            {
                Audio.sbuffer2.loadFromFile("audio/Damage 1.wav");
                Audio.sound2.setBuffer(Audio.sbuffer2);
                Audio.sound2.play();
                RemoveActorFromList(p_cActorList[i]);
                Experience = Experience + 1;
                current_map.nOccupied[attack_Y][attack_X] = 0;
                Player.Gold = Player.Gold + 10;
                Game.current_actors = Game.current_actors -1;
            }
        }
    }
}

void Player_State::died()
{
    int i = 0;
    window.setView(totalview);
    window.draw(Game.sGameBackground);
    Game.Gametext("Game over! You died!");
    Game.gametext = 0;
    window.setView(view1);
    current_map.DrawMap();
    current_map.DrawItems();
    DrawPlayer(0,0,0,0);
    window.setView(totalview);
    Game.DrawItemList(0);
    window.display();
    Audio.sbuffer2.loadFromFile("audio/Damage 1.wav");
    Audio.sound2.setBuffer(Audio.sbuffer2);
    Audio.sound2.play();
    while(i == 0)
    {
        while (window.pollEvent(Game.event))
        {
            switch(Game.event.type)
            {
            case sf::Event::KeyPressed:
                switch(Game.event.key.code)
                {
                case sf::Keyboard::Return:
                    i = 1;
                    Game.Initialize();
                    break;
                case sf::Keyboard::Escape:
                    Audio.play_music(-2);
                    Game.menu();
                    Audio.play_music(-1);
                    break;
                default:
                    break;
                }
                break;
            }
        }
    }
}

void Player_State::Shoot_Arrow(float gametime)
{
    bool Player_has_bow = false;
    bool Player_has_arrows = false;
    bool Player_has_rocks = false;
    int arrow_slot = 0;
    int rock_slot = 0;
    int damage = 0;
    int player_x = 3;
    int player_y = 3;
    int nShootable[7][7] = {0};
    int range = 0;
    nShootable[player_y][player_x] = 1;
    if(current_map.ispassable(Player.position_x - 1, Player.position_y, true, false))
    {
        nShootable[player_y][player_x - 1] = 1;
        if(current_map.ispassable(Player.position_x - 2, Player.position_y, true, false))
        {
            nShootable[player_y][player_x - 2] = 1;
            if(current_map.ispassable(Player.position_x - 3, Player.position_y, true, false))
            {
                nShootable[player_y][player_x - 3] = 1;
            }
        }
    }
    if(current_map.ispassable(Player.position_x + 1, Player.position_y, true, false))
    {
        nShootable[player_y][player_x + 1] = 1;
        if(current_map.ispassable(Player.position_x + 2, Player.position_y, true, false))
        {
            nShootable[player_y][player_x + 2] = 1;
            if(current_map.ispassable(Player.position_x + 3, Player.position_y, true, false))
            {
                nShootable[player_y][player_x + 3] = 1;
            }
        }
    }

    if(current_map.ispassable(Player.position_x, Player.position_y + 1, true, false))
    {
        nShootable[player_y + 1][player_x] = 1;
        if(current_map.ispassable(Player.position_x, Player.position_y + 2, true, false))
        {
            nShootable[player_y + 2][player_x] = 1;
            if(current_map.ispassable(Player.position_x, Player.position_y + 3, true, false))
            {
                nShootable[player_y + 3][player_x] = 1;
            }
        }
    }

    if(current_map.ispassable(Player.position_x, Player.position_y - 1, true, false))
    {
        nShootable[player_y - 1][player_x] = 1;
        if(current_map.ispassable(Player.position_x, Player.position_y - 2, true, false))
        {
            nShootable[player_y - 2][player_x] = 1;
            if(current_map.ispassable(Player.position_x, Player.position_y - 3, true, false))
            {
                nShootable[player_y - 3][player_x] = 1;
            }
        }
    }

    if(current_map.ispassable(Player.position_x -1, Player.position_y - 1, true, false))
    {
        nShootable[player_y - 1][player_x - 1] = 1;
        if(current_map.ispassable(Player.position_x - 2, Player.position_y - 2, true, false))
        {
            nShootable[player_y - 2][player_x - 2] = 1;
            if(current_map.ispassable(Player.position_x - 3, Player.position_y - 3, true, false))
            {
                nShootable[player_y - 3][player_x - 3] = 1;
            }
        }
    }

    if(current_map.ispassable(Player.position_x + 1, Player.position_y + 1, true, false))
    {
        nShootable[player_y + 1][player_x + 1] = 1;
        if(current_map.ispassable(Player.position_x + 2, Player.position_y + 2, true, false))
        {
            nShootable[player_y + 2][player_x + 2] = 1;
            if(current_map.ispassable(Player.position_x + 3, Player.position_y + 3, true, false))
            {
                nShootable[player_y + 3][player_x + 3] = 1;
            }
        }
    }

    if(current_map.ispassable(Player.position_x + 1, Player.position_y - 1, true, false))
    {
        nShootable[player_y - 1][player_x + 1] = 1;
        if(current_map.ispassable(Player.position_x + 2, Player.position_y - 2, true, false))
        {
            nShootable[player_y - 2][player_x + 2] = 1;
            if(current_map.ispassable(Player.position_x + 3, Player.position_y - 3, true, false))
            {
                nShootable[player_y - 3][player_x + 3] = 1;
            }
        }
    }

    if(current_map.ispassable(Player.position_x - 1, Player.position_y + 1, true, false))
    {
        nShootable[player_y + 1][player_x - 1] = 1;
        if(current_map.ispassable(Player.position_x - 2, Player.position_y + 2, true, false))
        {
            nShootable[player_y + 2][player_x - 2] = 1;
            if(current_map.ispassable(Player.position_x - 3, Player.position_y + 3, true, false))
            {
                nShootable[player_y + 3][player_x - 3] = 1;
            }
        }
    }
    if(nShootable[player_y - 1][player_x - 1] == 1 || nShootable[player_y - 2][player_x] == 1)
    {
        if(current_map.ispassable(Player.position_x - 1, Player.position_y - 2, true, false))
        {
            nShootable[player_y - 2][player_x - 1] = 1;
        }
    }
    if(nShootable[player_y - 1][player_x - 1] == 1 || nShootable[player_y][player_x - 2] == 1)
    {
        if(current_map.ispassable(Player.position_x - 2, Player.position_y - 1, true, false))
        {
            nShootable[player_y - 1][player_x - 2] = 1;
        }
    }

    if(nShootable[player_y + 1][player_x - 1] == 1 || nShootable[player_y + 2][player_x] == 1)
    {
        if(current_map.ispassable(Player.position_x - 1, Player.position_y - 2, true, false))
        {
            nShootable[player_y + 2][player_x - 1] = 1;
        }
    }
    if(nShootable[player_y + 1][player_x - 1] == 1 || nShootable[player_y][player_x - 2] == 1)
    {
        if(current_map.ispassable(Player.position_x - 2, Player.position_y + 1, true, false))
        {
            nShootable[player_y + 1][player_x - 2] = 1;
        }
    }

    if(nShootable[player_y + 1][player_x + 1] == 1 || nShootable[player_y + 2][player_x] == 1)
    {
        if(current_map.ispassable(Player.position_x + 1, Player.position_y - 2, true, false))
        {
            nShootable[player_y + 2][player_x + 1] = 1;
        }
    }
    if(nShootable[player_y + 1][player_x + 1] == 1 || nShootable[player_y][player_x + 2] == 1)
    {
        if(current_map.ispassable(Player.position_x + 2, Player.position_y + 1, true, false))
        {
            nShootable[player_y + 1][player_x + 2] = 1;
        }
    }
    if(nShootable[player_y - 1][player_x + 1] == 1 || nShootable[player_y - 2][player_x] == 1)
    {
        if(current_map.ispassable(Player.position_x + 1, Player.position_y - 2, true, false))
        {
            nShootable[player_y - 2][player_x + 1] = 1;
        }
    }
    if(nShootable[player_y - 1][player_x + 1] == 1 || nShootable[player_y][player_x + 2] == 1)
    {
        if(current_map.ispassable(Player.position_x + 2, Player.position_y - 1, true, false))
        {
            nShootable[player_y - 1][player_x + 2] = 1;
        }
    }
//blauwe hokjes
    if(nShootable[player_y - 3][player_x] == 1 || nShootable[player_y - 2][player_x - 1] == 1)
    {
        if(current_map.ispassable(Player.position_x - 1, Player.position_y - 3, true, false))
        {
            nShootable[player_y - 3][player_x - 1] = 1;
        }
    }
    if(nShootable[player_y - 3][player_x -1] == 1 || nShootable[player_y - 2][player_x - 2] == 1)
    {
        if(current_map.ispassable(Player.position_x - 2, Player.position_y - 3, true, false))
        {
            nShootable[player_y - 3][player_x - 2] = 1;
        }
    }
    if(nShootable[player_y][player_x -3] == 1 || nShootable[player_y - 1][player_x - 2] == 1)
    {
        if(current_map.ispassable(Player.position_x - 3, Player.position_y - 1, true, false))
        {
            nShootable[player_y - 1][player_x - 3] = 1;
        }
    }
    if(nShootable[player_y-2][player_x -2] == 1 || nShootable[player_y - 1][player_x - 3] == 1)
    {
        if(current_map.ispassable(Player.position_x - 3, Player.position_y - 2, true, false))
        {
            nShootable[player_y - 2][player_x - 3] = 1;
        }
    }
    if(nShootable[player_y + 3][player_x] == 1 || nShootable[player_y + 2][player_x - 1] == 1)
    {
        if(current_map.ispassable(Player.position_x - 1, Player.position_y + 3, true, false))
        {
            nShootable[player_y + 3][player_x - 1] = 1;
        }
    }
    if(nShootable[player_y + 3][player_x -1] == 1 || nShootable[player_y + 2][player_x - 2] == 1)
    {
        if(current_map.ispassable(Player.position_x - 2, Player.position_y + 3, true, false))
        {
            nShootable[player_y + 3][player_x - 2] = 1;
        }
    }
    if(nShootable[player_y][player_x -3] == 1 || nShootable[player_y + 1][player_x - 2] == 1)
    {
        if(current_map.ispassable(Player.position_x - 3, Player.position_y + 1, true, false))
        {
            nShootable[player_y + 1][player_x - 3] = 1;
        }
    }
    if(nShootable[player_y+2][player_x -2] == 1 || nShootable[player_y + 1][player_x - 3] == 1)
    {
        if(current_map.ispassable(Player.position_x - 3, Player.position_y + 2, true, false))
        {
            nShootable[player_y + 2][player_x - 3] = 1;
        }
    }

    if(nShootable[player_y - 3][player_x] == 1 || nShootable[player_y - 2][player_x + 1] == 1)
    {
        if(current_map.ispassable(Player.position_x + 1, Player.position_y - 3, true, false))
        {
            nShootable[player_y - 3][player_x + 1] = 1;
        }
    }
    if(nShootable[player_y - 3][player_x + 1] == 1 || nShootable[player_y - 2][player_x + 2] == 1)
    {
        if(current_map.ispassable(Player.position_x + 2, Player.position_y - 3, true, false))
        {
            nShootable[player_y - 3][player_x + 2] = 1;
        }
    }
    if(nShootable[player_y][player_x +3] == 1 || nShootable[player_y - 1][player_x + 2] == 1)
    {
        if(current_map.ispassable(Player.position_x + 3, Player.position_y - 1, true, false))
        {
            nShootable[player_y - 1][player_x + 3] = 1;
        }
    }
    if(nShootable[player_y-2][player_x +2] == 1 || nShootable[player_y - 1][player_x + 3] == 1)
    {
        if(current_map.ispassable(Player.position_x + 3, Player.position_y - 2, true, false))
        {
            nShootable[player_y - 2][player_x + 3] = 1;
        }
    }

    if(nShootable[player_y + 3][player_x] == 1 || nShootable[player_y + 2][player_x + 1] == 1)
    {
        if(current_map.ispassable(Player.position_x + 1, Player.position_y + 3, true, false))
        {
            nShootable[player_y + 3][player_x + 1] = 1;
        }
    }
    if(nShootable[player_y + 3][player_x -1] == 1 || nShootable[player_y + 2][player_x + 2] == 1)
    {
        if(current_map.ispassable(Player.position_x + 2, Player.position_y + 3, true, false))
        {
            nShootable[player_y + 3][player_x + 2] = 1;
        }
    }

    if(nShootable[player_y][player_x +3] == 1 || nShootable[player_y + 1][player_x + 2] == 1)
    {
        if(current_map.ispassable(Player.position_x + 3, Player.position_y + 1, true, false))
        {
            nShootable[player_y + 1][player_x + 3] = 1;
        }
    }
    if(nShootable[player_y+2][player_x +2] == 1 || nShootable[player_y + 1][player_x + 3] == 1)
    {
        if(current_map.ispassable(Player.position_x + 3, Player.position_y + 2, true, false))
        {
            nShootable[player_y + 2][player_x + 3] = 1;
        }
    }
    for(int i = 0; i <10; i++)
    {
        if(nInventory[i] == 6)
        {
            Player_has_bow = true;
        }
        if(nInventory[i] == 7)
        {
            Player_has_arrows = true;
            arrow_slot = i;
        }
        if(nInventory[i] == 2)
        {
            damage = 10;
            range = 2;
            rock_slot = i;
        }
    }
    if(Player_has_bow && Player_has_arrows)
    {
        range = 3;
        damage = 20;
    }
    if(damage != 0)
    {
        sf::Clock clockMain;
        //Oke je kan schieten waar wil je schiten?
        bool pressed_enter = false;
        bool focus = true;
        int cursor_x = player_x;
        int cursor_y = player_y;
        int tchange_x = 0;
        int tchange_y = 0;
        float timepressed = 0;
        float timepressed_x = 0;
        float timepressed_y = 0;
        while(!pressed_enter)
        {
            sf::Time elapsedMain = clockMain.getElapsedTime();
            int change_x = 0;
            int change_y = 0;
            while (window.pollEvent(Game.event))
            {
                switch(Game.event.type)
                {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::LostFocus:
                    focus = false;
                    break;
                case sf::Event::GainedFocus:
                    focus = true;
                    break;
                }
            }
            if(focus == true)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    return;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    pressed_enter = true;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (timepressed_y + 0.3) < elapsedMain.asSeconds())
                {
                    timepressed = elapsedMain.asSeconds();
                    timepressed_y = elapsedMain.asSeconds();
                    change_y =  -1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (timepressed_y + 0.3) < elapsedMain.asSeconds())
                {
                    timepressed = elapsedMain.asSeconds();
                    timepressed_y = elapsedMain.asSeconds();
                    change_y =  +1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (timepressed_x + 0.3) < elapsedMain.asSeconds())
                {
                    timepressed = elapsedMain.asSeconds();
                    timepressed_x = elapsedMain.asSeconds();
                    change_x =  +1;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (timepressed_x + 0.3) < elapsedMain.asSeconds())
                {
                    timepressed = elapsedMain.asSeconds();
                    timepressed_x = elapsedMain.asSeconds();
                    change_x = -1;
                }
                if(change_x != 0)
                {
                    tchange_x = tchange_x + change_x;
                    if(tchange_x <= range && tchange_x >= -range)
                    {
                        if(nShootable[cursor_y][cursor_x + change_x] == 1)
                        {
                            cursor_x = cursor_x + change_x;
                        }
                        else
                        {
                            tchange_x = tchange_x - change_x;
                        }
                    }
                    else
                    {
                        tchange_x = tchange_x - change_x;
                    }
                }
                if(change_y != 0)
                {
                    tchange_y = tchange_y + change_y;
                    if(tchange_y <= range && tchange_y >= -range )
                    {
                        if(nShootable[cursor_y + change_y][cursor_x] == 1)
                        {
                            cursor_y = cursor_y + change_y;
                        }
                        else
                        {
                            tchange_y = tchange_y - change_y;
                        }
                    }
                    else
                    {
                        tchange_y = tchange_y - change_y;
                    }
                }
            }
            int tempx1 = (Player.position_x+tchange_x)*32;
            int tempy1 = (Player.position_y+tchange_y)*32;
            Game.sCrosshair.setPosition(tempx1, tempy1);
            window.setView(totalview);
            window.draw(Game.sGameBackground);
            Game.Gametext("Where do you want to shoot? Press Enter to confirm.");
            Game.gametext = 0;
            window.setView(view1);
            current_map.DrawMap();
            current_map.DrawItems();
            for(int i = 0; i < MAX_ACTORS; i++ )
            {
                if(p_cActorList[i] != NULL )
                {
                    p_cActorList[i]->Draw(gametime);
                }
            }
            DrawPlayer(0,0,0,0);
            window.draw(Game.sCrosshair);
            window.setView(totalview);
            Game.DrawItemList(0);
            window.display();
        }
        if(pressed_enter)
        {
            if(Player_has_bow && Player_has_arrows)
            {
                aInventory[arrow_slot] = aInventory[arrow_slot] - 1;
                if(aInventory[arrow_slot] == 0)
                {
                    nInventory[arrow_slot] = 0;
                    Player.attack =  Player.attack - current_map.nItemDMG[7];
                    Player.armor = Player.armor - current_map.nItemARM[7];
                }
            }
            else if(damage = 10)
            {
                aInventory[rock_slot] = aInventory[rock_slot] - 1;
                if(aInventory[rock_slot] == 0)
                {
                    nInventory[rock_slot] = 0;
                    Player.attack =  Player.attack - current_map.nItemDMG[2];
                    Player.armor = Player.armor - current_map.nItemARM[2];
                }
            }
            bool enemy_hit = false;
            for(int i = 0; i < MAX_ACTORS; i++ )
            {
                if(p_cActorList[i] != NULL )
                {
                    if(p_cActorList[i]->TakeDamage(Player.position_x+tchange_x, Player.position_y+tchange_y, 20))
                    {
                        enemy_hit = true;
                        Audio.sbuffer2.loadFromFile("audio/Damage 1.wav");
                        Audio.sound2.setBuffer(Audio.sbuffer2);
                        Audio.sound2.play();
                        if(current_map.nItemArray[Player.position_y+tchange_y][Player.position_x+tchange_x] == 0)
                        {
                            if(Player_has_bow && Player_has_arrows)
                            {
                                current_map.nItemArray[Player.position_y+tchange_y][Player.position_x+tchange_x] = 7;
                            }
                            else
                            {
                                current_map.nItemArray[Player.position_y+tchange_y][Player.position_x+tchange_x] = 2;
                            }
                        }
                        RemoveActorFromList(p_cActorList[i]);
                        Experience = Experience + 1;
                        current_map.nOccupied[Player.position_y+tchange_y][Player.position_x+tchange_x] = 0;
                        Player.Gold = Player.Gold + 10;
                        Game.current_actors = Game.current_actors -1;
                    }
                }
            }
            if(!enemy_hit)
            {
                if(current_map.nItemArray[Player.position_y+tchange_y][Player.position_x+tchange_x] == 0)
                {
                    if(Player_has_bow && Player_has_arrows)
                    {
                        current_map.nItemArray[Player.position_y+tchange_y][Player.position_x+tchange_x] = 7;
                    }
                    else if(damage = 10)
                    {
                        current_map.nItemArray[Player.position_y+tchange_y][Player.position_x+tchange_x] = 2;
                    }
                }
            }
        }
    }

}

int Player_State::Pick_Up_Item()
{
    if(current_map.nItemArray[Player.position_y][Player.position_x] != 0)
    {
        int item = current_map.nItemArray[Player.position_y][Player.position_x];
        int exist = 0;
        if (item == 9)
        {
            //dit is een boot; die kan je niet pakken!
            return 1;
        }
        for( int i = 0; i < 10; i++ )
        {
            if(Player.nInventory[i] == item)
            {
                exist = 1;
                Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
                Audio.sound4.setBuffer(Audio.sbuffer4);
                Audio.sound4.play();
                Player.aInventory[i] = Player.aInventory[i] + 1;
                current_map.nItemArray[Player.position_y][Player.position_x] = 0;
                break;
            }
        }
        if(exist == 0)
        {
            for( int i = 0; i < 10; i++ )
            {
                if(Player.nInventory[i] == 0)
                {
                    Audio.sbuffer4.loadFromFile("audio/schiet 2.wav");
                    Audio.sound4.setBuffer(Audio.sbuffer4);
                    Audio.sound4.play();
                    Player.armor = Player.armor + current_map.nItemARM[item];
                    Player.attack = Player.attack + current_map.nItemDMG[item];
                    Player.nInventory[i] = item;
                    Player.aInventory[i] = 1;
                    current_map.nItemArray[Player.position_y][Player.position_x] = 0;
                    break;
                }
            }
        }
        return 0;
    }
    else
    {
        //hier ligt niks
        return 2;
    }
}

void Player_State::Talk(float currenttime)
{
    window.setView(totalview);
    window.draw(Game.sGameBackground);
    int attack_X = Player.position_x;
    int attack_Y = Player.position_y;
    switch (Player.porientation)
    {
    case 1:
        attack_Y = attack_Y - 1;
        break;
    case 2:
        attack_Y = attack_Y + 1;
        break;
    case 3:
        attack_X = attack_X + 1;
        break;
    case 4:
        attack_X = attack_X - 1;
        break;
    }
    for(int i = 0; i < 5; i++ )
    {
        if(p_cfriendly_npcList[i] != NULL )
        {
            p_cfriendly_npcList[i]->interact_npc(attack_X, attack_Y, currenttime);
        }
    }
    for(int i = 0; i < 5; i++ )
    {
        if(itemShopList[i] != NULL )
        {
            itemShopList[i]->interactWithShop(attack_X, attack_Y, currenttime);
        }
    }
    if(Game.gametext == 0)
    {
        Game.Gametext("You started talking in yourself... It looks quite silly!");
    }
    int i = 0;
    Game.Gametext("");
    Game.Gametext("                                       Please press ENTER to continue...");
    Game.gametext = 0;
    window.setView(view1);
    current_map.DrawMap();
    current_map.DrawItems();
    for(int i = 0; i < MAX_ACTORS; i++ )
    {
        if(p_cActorList[i] != NULL )
        {
            p_cActorList[i]->Draw(currenttime);
        }
    }
    for(int i = 0; i < 5; i++ )
    {
        if(p_cfriendly_npcList[i] != NULL )
        {
            p_cfriendly_npcList[i]->draw(currenttime);
        }
    }
    Player.DrawPlayer(0,0,0,0);
    window.setView(totalview);
    Game.DrawItemList(0);
    window.display();
    while(i!= -1)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            i = -1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            i = -1;
        }
    }
}

