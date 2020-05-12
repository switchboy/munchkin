#include <sstream>
#include <fstream>
#include <iostream>
#include "gameengine.h"
#include "player.h"
#include "gamemap.h"
#include "npc.h"
#include "soundsystem.h"
#include "mapEditor.cpp"

Game_Engine Game;

int Game_Engine::getMapNumber()
{
    return this->mapnr;
}

bool Game_Engine::getDungeon()
{
    return this->dungeon;
}


void Game_Engine::loadtextures()
{
    if(GameBackground.loadFromFile("Textures/background.png"))
    {
        sGameBackground.setTexture(GameBackground);
        sf::Vector2u bgsize = GameBackground.getSize();
        sGameBackground.scale((float) window_x/bgsize.x, (float) window_y/bgsize.y);
    }

    //items
    if(Item_Potion.loadFromFile("Textures/potion.png"))
    {
        sItem_Potion.setTexture(Item_Potion);
    }
    if(Item_ManaPotion.loadFromFile("Textures/manaPotion.png"))
    {
        sItem_ManaPotion.setTexture(Item_ManaPotion);
    }

    if(Item_ManaPotionShop.loadFromFile("Textures/manaPotionShop.png"))
    {
        sItem_ManaPotionShop.setTexture(Item_ManaPotionShop);
    }

    if(Item_Ship.loadFromFile("Textures/ship.png"))
    {
        sItem_Ship.setTexture(Item_Ship);
    }

    if(Item_Rock.loadFromFile("Textures/rock.png"))
    {
        sItem_Rock.setTexture(Item_Rock);
    }

    if(Item_Key.loadFromFile("Textures/key.png"))
    {
        sItem_Key.setTexture(Item_Key);
    }

    if(Item_Pickaxe.loadFromFile("Textures/pickaxe.png"))
    {
        sItem_Pickaxe.setTexture(Item_Pickaxe);
    }

    if(Item_WoodenSword.loadFromFile("Textures/wooden_sword.png"))
    {
        sItem_WoodenSword.setTexture(Item_WoodenSword);
    }

    if(Item_Bow.loadFromFile("Textures/bow.png"))
    {
        sItem_Bow.setTexture(Item_Bow);
    }

    if(Item_Arrow.loadFromFile("Textures/arrow.png"))
    {
        sItem_Arrow.setTexture(Item_Arrow);
    }

    if(Item_Shield.loadFromFile("Textures/shield.png"))
    {
        sItem_Shield.setTexture(Item_Shield);
    }




    //ShopItems
    if(Item_PotionShop.loadFromFile("Textures/potionShop.png"))
    {
        sItem_PotionShop.setTexture(Item_PotionShop);
    }

    if(Item_ShipShop.loadFromFile("Textures/shipShop.png"))
    {
        sItem_ShipShop.setTexture(Item_ShipShop);
    }

    if(Item_RockShop.loadFromFile("Textures/rockShop.png"))
    {
        sItem_RockShop.setTexture(Item_RockShop);
    }

    if(Item_KeyShop.loadFromFile("Textures/keyShop.png"))
    {
        sItem_KeyShop.setTexture(Item_KeyShop);
    }

    if(Item_PickaxeShop.loadFromFile("Textures/pickaxeShop.png"))
    {
        sItem_PickaxeShop.setTexture(Item_PickaxeShop);
    }

    if(Item_WoodenSwordShop.loadFromFile("Textures/wooden_swordShop.png"))
    {
        sItem_WoodenSwordShop.setTexture(Item_WoodenSwordShop);
    }

    if(Item_BowShop.loadFromFile("Textures/bowShop.png"))
    {
        sItem_BowShop.setTexture(Item_BowShop);
    }

    if(Item_ArrowShop.loadFromFile("Textures/arrowShop.png"))
    {
        sItem_ArrowShop.setTexture(Item_ArrowShop);
    }

    if(Item_ShieldShop.loadFromFile("Textures/shieldShop.png"))
    {
        sItem_ShieldShop.setTexture(Item_ShieldShop);
    }


    //map tiles
    if(TileWater0.loadFromFile("Textures/water0.png") & TileWater1.loadFromFile("Textures/water1.png") & TileWater2.loadFromFile("Textures/water2.png") & TileWater3.loadFromFile("Textures/water3.png"))
    {
        sTileWater.setTexture(TileWater0);
    }

    if(Tile_RockFloor.loadFromFile("Textures/rockfloor.png"))
    {
        sTile_RockFloor.setTexture(Tile_RockFloor);
    }

    if(Tile_Wall.loadFromFile("Textures/wall.png"))
    {
        sTile_Wall.setTexture(Tile_Wall);
    }

    if(Tile_ClosedDoor.loadFromFile("Textures/closeddoor.png"))
    {
        sTile_ClosedDoor.setTexture(Tile_ClosedDoor);
    }

    if(Tile_OpenDoor.loadFromFile("Textures/opendoor.png"))
    {
        sTile_OpenDoor.setTexture(Tile_OpenDoor);
    }

    if(Tile_Grass.loadFromFile("Textures/grass.png"))
    {
        sTile_Grass.setTexture(Tile_Grass);
    }

    if(Tile_Tree.loadFromFile("Textures/tree.png"))
    {
        sTile_Tree.setTexture(Tile_Tree);
    }

    if(TilePrev.loadFromFile("Textures/prevlevel.png"))
    {
        sTilePrev.setTexture(TilePrev);
    }

    if(TileNext.loadFromFile("Textures/finish.png"))
    {
        sTileNext.setTexture(TileNext);
    }

    if(TileDungeon.loadFromFile("Textures/todungeon.png"))
    {
        sTileDungeon.setTexture(TileDungeon);
    }

    if(Tile_LockedDoor.loadFromFile("Textures/lockeddoor.png"))
    {
        sTile_LockedDoor.setTexture(Tile_LockedDoor);
    }

    if(tActor.loadFromFile("Textures/brute.png"))
    {
        sActor.setTexture(tActor);
        sActor.setOrigin( 16,16);
    }

    if(tNPC.loadFromFile("Textures/villager.png"))
    {
        sNPC.setTexture(tNPC);
        sNPC.setOrigin( 16,16);
    }

    if(tShop.loadFromFile("Textures/shop.png"))
    {
        sShop.setTexture(tShop);
        sShop.setOrigin(16,16);
    }

    //player sprites
    playerInBoat.loadFromFile("Textures/playerinboat.png");
    tplayerUp.loadFromFile("Textures/playerup.png");
    splayer.setTexture(tplayerUp);
    splayer.setOrigin( 16,16);

    //game elements
    if(Crosshair.loadFromFile("Textures/crosshair.png"))
    {
        sCrosshair.setTexture(Crosshair);
    }

}

int Game_Engine::Watertexture(int watertile)
{
    switch(watertile)
    {
    case 0:
        sTileWater.setTexture(TileWater0);
        return 1;
        break;
    case 1:
        sTileWater.setTexture(TileWater1);
        return 2;
        break;
    case 2:
        sTileWater.setTexture(TileWater2);
        return 3;
        break;
    case 3:
        sTileWater.setTexture(TileWater3);
        return 0;
        break;
    default:
        sTileWater.setTexture(TileWater0);
        return 0;
        break;
    }
}

void Game_Engine::DrawItemList(int shop)
{
    if (!font.loadFromFile("fonts/TrajanPro-Regular.otf"))
    {
        // error...
    }
    text.setFont(font);
    text.setCharacterSize(item_list_y);
    text.setColor(sf::Color::White);

    std::stringstream player_level;
    player_level << "Level: " << (int)Player.Lvl;
    text.setString(player_level.str());
    int textx = item_list_x, texty = item_list_y;
    text.setPosition(textx, texty);
    window.draw(text);

    std::stringstream player_xp;
    player_xp << "EXP: " << (int)Player.Experience << "/" << (int)pow(5, Player.Lvl);
    text.setString(player_xp.str());
    texty = texty + (item_list_y + round(item_list_y/10));
    text.setPosition(textx, texty);
    window.draw(text);

    std::stringstream health_nrs;
    health_nrs << "Health:  " << (int)Player.health << "/" << (int)Player.max_health;
    text.setString(health_nrs.str());
    texty = texty + (item_list_y + round(item_list_y/10));
    text.setPosition(textx, texty);
    window.draw(text);

    std::stringstream mana_nrs;
    mana_nrs << "Mana:  " << (int)Player.mana << "/" << (int)Player.max_mana;
    text.setString(mana_nrs.str());
    texty = texty + (item_list_y + round(item_list_y/10));
    text.setPosition(textx, texty);
    window.draw(text);

    std::stringstream gold_nrs;
    gold_nrs << "Gold:    " << Player.Gold;
    text.setString(gold_nrs.str());
    texty = texty + (item_list_y + round(item_list_y/10));
    text.setPosition(textx, texty);
    window.draw(text);

    std::stringstream dmg_nrs;
    dmg_nrs << "Damage:  " << Player.attack;
    text.setString(dmg_nrs.str());
    texty = texty = texty + ((item_list_y*2) + round(item_list_y/10));
    text.setPosition(textx, texty);
    window.draw(text);

    std::stringstream mgds_nrs;
    mgds_nrs << "Magic DMG:    " << Player.magic_attack;
    text.setString(mgds_nrs.str());
    texty = texty + (item_list_y + round(item_list_y/10));
    text.setPosition(textx, texty);
    window.draw(text);

    std::stringstream arm_nrs;
    arm_nrs << "Armor:   " << (int)Player.armor;
    text.setString(arm_nrs.str());
    texty = texty + (item_list_y + round(item_list_y/10));
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + (item_list_y + round(item_list_y/10));
    text.setString("Items: (max 10)");
    texty = texty + (item_list_y + round(item_list_y/10));
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/2);
    for( int i = 0; i < 10; i++ )
    {
        std::stringstream item_text;
        item_text << (int) i;
        text.setCharacterSize(round(item_list_y/1.5));
        texty = texty + round(item_list_y/1.5);

        item_text << ": " << Game.itemNameList[Player.nInventory[i]];
        if(Player.aInventory[i] > 0)
        {
            item_text << " - " << (int)Player.aInventory[i] << " x";
            if(shop != 0)
            {
                int itemPrice;
                itemPrice = round( Game.itemPriceList[Player.nInventory[i]])* (1-(shop/100.00)) ;
                item_text << "    Gold:  " << itemPrice;
            }
        }
        text.setString(item_text.str());
        text.setPosition(textx, texty);
        window.draw(text);
    }
    text.setCharacterSize(item_list_y);
    texty = texty + item_list_y*2;
    text.setString("Abilities");
    text.setPosition(textx, texty);
    window.draw(text);

    text.setCharacterSize(round(item_list_y/1.5));
    texty = texty + item_list_y;
    text.setString("'E' = Pick-up item");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/1.5);
    text.setString("'F' = Use item");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/1.5);
    text.setString("'D' = Drop Item");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/1.5);
    text.setString("'W' = For doors");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/1.5);
    text.setString("'A' = Attack");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/1.5);
    text.setString("'Q' = Magic Attack");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/1.5);
    text.setString("'S' = Ranged Attack");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/1.5);
    text.setString("'R' = Talk");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + round(item_list_y/1.5);
    text.setString("'B' = Use Boat");
    text.setPosition(textx, texty);
    window.draw(text);

    texty = texty + item_list_y*2;
    text.setString("Current map: "+mapname_name);
    text.setPosition(textx, texty);
    window.draw(text);
}

void Game_Engine::Gametext(sf::String detext)
{
    int GTY = gametext_y + (round(gametext_x)/2)*gametext;
    gametext = gametext + 1;
    text.setCharacterSize(round(gametext_x)/2);
    text.setPosition(gametext_x, GTY);
    text.setString(detext);
    window.draw(text);
}

void Game_Engine::save_state(std::string mapname)
{
    std::string filename = "maps/" + mapname;
    filename.append("p.txt");
    std::ofstream myfile(filename.c_str(), std::ios::out);
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            myfile << current_map.nMapArray[i][j];
            if(j < MAP_WIDTH-1)
            {
                myfile << " ";
            }
        }
        myfile << "\n";
    }
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            myfile << current_map.nItemArray[i][j];
            if(j < MAP_WIDTH-1)
            {
                myfile << " ";
            }
        }
        myfile <<"\n";
    }
    for (int i=0; i < 5; i++)
    {
        for( int j =0; j < 3; j++)
        {
            if(p_cfriendly_npcList[i] != NULL)
            {
                myfile << p_cfriendly_npcList[i]->getValue(j);
                myfile << " ";
            }
            else
            {
                myfile << "0 ";
            }
        }
        if(p_cfriendly_npcList[i] != NULL)
        {
            myfile << "1 \n";
        }
        else
        {
            myfile << "0 \n";
        }
    }
    myfile.close();
}

void Game_Engine::move_view(int change_x, int change_y, float currentTime, float timepressed,  float timepressed_x, float timepressed_y)
{
    float tempx, tempy;
    if(timepressed + 0.3 > currentTime)
    {
        if(timepressed_x + 0.3 > currentTime)
        {
            switch (change_x)
            {
            case -1:
                tempx = Player.position_x + 1 - (1*((currentTime-timepressed_x)/0.3));
                break;
            case 0:
                tempx = Player.position_x;
                break;
            case 1:
                tempx = Player.position_x -1 + (1*((currentTime-timepressed_x)/0.3));
                break;
            }
        }
        else
        {
            tempx = Player.position_x;
        }
        if(timepressed_y + 0.3 > currentTime)
        {
            switch (change_y)
            {
            case -1:
                tempy = Player.position_y + 1 - (1*((currentTime-timepressed_y)/0.3));
                break;
            case 0:
                tempy = Player.position_y;
                break;
            case 1:
                tempy = Player.position_y - 1 + (1*((currentTime-timepressed_y)/0.3));
                break;
            }
        }
        else
        {
            tempy = Player.position_y;
        }
        int tempx1 = tempx *32;
        int tempy1 = tempy *32;
        view1.reset(sf::FloatRect(tempx1-(viewport_x/2), tempy1-(viewport_y/2), viewport_x, viewport_y));
    }
    else
    {
        view1.reset(sf::FloatRect((Player.position_x*32)-(viewport_x/2), (Player.position_y*32)-(viewport_y/2), viewport_x, viewport_y));
    }
}

int Game_Engine::load_prev_level()
{
    enemies[0][mapnr] = current_actors;
    //load prev level
    std::stringstream tempmap1;
    tempmap1 << "map" << mapnr;
    std::string prevmapname = tempmap1.str();
    mapnr = mapnr -1;
    std::stringstream tempmap2;
    tempmap2 << "map" << mapnr;
    std::string mapname = tempmap2.str();
    save_state(prevmapname);
    std::string mapname2 = mapname;
    mapname2.append("p");
    if(mapnr <= highest_level)
    {
        if(!current_map.loadmap(mapname2))
        {
            if(!current_map.loadmap(mapname))
            {
                std::cout << "Map file not found!" << std::endl;
                window.close();
                return 21;
            }
        }
        current_map.spwan_location(0);
    }
    else
    {
        highest_level = mapnr;
        if(!current_map.loadmap(mapname))
        {
            std::cout << "Map file not found!" << std::endl;
            window.close();
            return 21;
        }
        current_map.spwan_location(0);
    }
    Audio.sbuffer5.loadFromFile("audio/next level.wav");
    Audio.sound5.setBuffer(Audio.sbuffer5);
    Audio.sound5.play();
}

int Game_Engine::load_next_level()
{
    enemies[0][mapnr] = current_actors;
    //load next level
    std::stringstream tempmap1;
    tempmap1 << "map" << mapnr;
    std::string prevmapname = tempmap1.str();
    mapnr = mapnr +1;
    std::stringstream tempmap2;
    tempmap2 << "map" << mapnr;
    std::string mapname = tempmap2.str();
    save_state(prevmapname);
    std::string mapname2 = mapname;
    mapname2.append("p");
    if(mapnr <= highest_level)
    {
        if(!current_map.loadmap(mapname2))
        {
            if(!current_map.loadmap(mapname))
            {
                std::cout << "Map file not found!" << std::endl;
                window.close();
                return 21;
            }
        }
        current_map.spwan_location(1);
    }
    else
    {
        highest_level = mapnr;
        if(!current_map.loadmap(mapname))
        {
            std::cout << "Map file not found!" << std::endl;
            window.close();
            return 21;
        }
        current_map.spwan_location(1);
    }
    Audio.sbuffer5.loadFromFile("audio/next level.wav");
    Audio.sound5.setBuffer(Audio.sbuffer5);
    Audio.sound5.play();
}

int Game_Engine::switch_dungeon()
{
    std::stringstream tempmap1;
    tempmap1 << "map" << mapnr;
    std::string prevmapname = tempmap1.str();
    if(mapnr < highest_level)
    {
        highest_level = mapnr;
    }
    std::stringstream tempmap2;
    tempmap2 << "map" << mapnr;
    std::string mapname = tempmap2.str();
    std::string mapname2 = mapname;
    mapname.append("p");
    mapname2.append("d");
    std::string mapname3 = mapname2;
    mapname3.append("p");
    if(!dungeon)
    {
        enemies[0][mapnr] = current_actors;
        dungeon = true;
        save_state(prevmapname);
        if(dungeon_visited[mapnr] == 1)
        {
            dungeon = true;
            if(!current_map.loadmap(mapname3))
            {
                std::cout << "Map file not found!" << std::endl;
                window.close();
                return 21;
            }
            current_map.spwan_location(2);
        }
        else
        {
            dungeon_visited[mapnr] = 1;
            dungeon = true;
            if(!current_map.loadmap(mapname2))
            {
                std::cout << "Map file not found!" << std::endl;
                window.close();
                return 21;
            }
            current_map.spwan_location(2);
        }
        Audio.play_music(1);
    }
    else
    {
        enemies[1][mapnr] = current_actors;
        save_state(mapname2);
        dungeon = false;
        if(!current_map.loadmap(mapname))
        {
            std::cout << "Map file not found!" << std::endl;
            window.close();
            return 21;
        }
        current_map.spwan_location(2);
        Audio.play_music(0);
    }
    Audio.sbuffer5.loadFromFile("audio/next level.wav");
    Audio.sound5.setBuffer(Audio.sbuffer5);
    Audio.sound5.play();
    return 0;
}

void Game_Engine::Initialize()
{
    Player.position_x = 4;
    Player.position_y = 5;
    Player.porientation = 1;
    for(int i=0; i<11; i++)
    {
        Player.nInventory[i] = 0;
        Player.aInventory[i] = 0;
    }
    Game.mapnr = 1;
    Game.highest_level = 1;
    Player.health = 100;
    Player.max_health = 100;
    Player.mana = 100;
    Player.max_mana=100;
    Player.Lvl = 1;
    Player.Experience = 1;
    Player.magic_attack = 25;
    Player.attack = 10;
    Player.armor = 10;
    Player.Gold = 0;
    Game.splayer.setPosition(32, 32);
    std::stringstream mapnames;
    mapnames << "maps/map" << Game.mapnr;
    std::string mapname = mapnames.str();
    for(int i = 0; i < 99; i++)
    {
        enemies[0][i] = 10;
    }
    for(int i = 0; i < 99; i++)
    {
        enemies[1][i] = 10;
    }
    if(!current_map.loadmap(mapname))
    {
        std::cout << "Map file not found!" << std::endl;
        window.close();
    }
}

void Game_Engine::menu()
{
    sf::Clock clockMain;
    bool continue_to_game = false;
    float timepressed = 0;
    bool pressed_enter = false;
    bool focus = true;
    int option_selected = 0;
    int options[4] = {3, 2, 2, 2};
    int low_limit_option[4] = {0, 0, 0, 0};
    int option_level = 0;
    if(this->game_in_progress)
    {
        low_limit_option[0] = -1;
    }
    if (!font.loadFromFile("fonts/TrajanPro-Regular.otf"))
    {
        // error...
    }
    text.setFont(font);

    while(!continue_to_game)
    {
        text.setCharacterSize(32);
        window.clear();
        sf::Time elapsedMain = clockMain.getElapsedTime();
        //
        //input gedeelte:
        //
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&& (timepressed + 0.2) < elapsedMain.asSeconds())
            {
                timepressed = elapsedMain.asSeconds();
                pressed_enter = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (timepressed + 0.2) < elapsedMain.asSeconds())
            {
                timepressed = elapsedMain.asSeconds();
                if(option_selected == low_limit_option[option_level])
                {
                    option_selected = options[option_level];
                }
                else
                {
                    option_selected = option_selected - 1;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (timepressed + 0.2) < elapsedMain.asSeconds())
            {
                timepressed = elapsedMain.asSeconds();
                if(option_selected == options[option_level])
                {
                    option_selected = low_limit_option[option_level];
                }
                else
                {
                    option_selected = option_selected + 1;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (timepressed + 0.2) < elapsedMain.asSeconds())
            {
                timepressed = elapsedMain.asSeconds();
                if(option_level > 0 && option_level < 2)
                {
                    option_level = option_level -1;
                    option_selected = 0;
                }
                else if (option_level == 2 || option_level == 3)
                {
                    option_level = 1;
                    option_selected = 0;
                }
            }
        }
        //
        //handel af wat er gebeurd als enter is ingetyped:
        //
        if(pressed_enter)
        {
            if(option_level == 0)
            {
                switch(option_selected)
                {
                case 0:
                    this->game_in_progress = true;
                    return;
                    break;
                case 1:
                    option_level = 1;
                    option_selected = 0;
                    break;
                case 2:
                    mapEditor();
                    break;
                case 3:
                    exit(0);
                    break;
                case -1:
                    Game.Initialize();
                    return;
                    break;
                }
            }
            else if(option_level == 1)
            {
                //Dit is het opties menu
                switch(option_selected)
                {
                case 0:
                    //go to graphics
                    option_level = 2;
                    option_selected = 2;
                    break;
                case 1:
                    //go to sound
                    option_level = 3;
                    option_selected = 2;
                    break;
                case 2:
                    //go back
                    option_level = 0;
                    option_selected = 0;
                    break;
                }
            }
            else if(option_level == 2)
            {
                //Dit is het graphics menu
                switch(option_selected)
                {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    //go back
                    option_level = 1;
                    option_selected = 0;
                    break;
                }
            }
            else if(option_level == 3)
            {
                //Dit is het sound menu
                switch(option_selected)
                {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    //go back
                    option_level = 1;
                    option_selected = 0;
                    break;
                }
            }
            pressed_enter = false;
        }
        //
        //Laat het menu zien:
        //
        int textx = (window_x/2)-120;
        int texty = (window_y/2)-80;
        if(option_level == 0)
        {
            //laat het hoofdmenu zien
            for(int i = 0; i <= options[0]; i++)
            {
                std::string menu_text;
                if(option_selected == i)
                {
                    text.setColor(sf::Color::White);
                }
                else
                {
                    text.setColor(sf::Color::Yellow);
                }
                switch(i)
                {
                case 0:
                    if(this->game_in_progress)
                    {
                        menu_text = "Resume Game";
                    }
                    else
                    {
                        menu_text = "Play Game";
                    }
                    break;
                case 1:
                    menu_text = "Options";
                    break;
                case 2:
                    menu_text = "Level editor";
                    break;
                case 3:
                    menu_text = "Quit";
                    break;
                }
                text.setPosition(textx, texty);
                text.setString(menu_text);
                window.draw(text);
                texty = texty + 38;
            }
            if(this->game_in_progress)
            {
                if(option_selected == -1)
                {
                    text.setColor(sf::Color::White);
                }
                else
                {
                    text.setColor(sf::Color::Yellow);
                }
                texty = (window_y/2)-118;
                text.setPosition(textx, texty);
                text.setString("New Game");
                window.draw(text);
            }
        }
        if(option_level == 1)
        {
            //laat het optes menu zien
            for(int i = 0; i <= options[0]; i++)
            {
                std::string menu_text;
                if(option_selected == i)
                {
                    text.setColor(sf::Color::White);
                }
                else
                {
                    text.setColor(sf::Color::Yellow);
                }
                switch(i)
                {
                case 0:
                    menu_text = "Graphics";
                    break;
                case 1:
                    menu_text = "Sound";
                    break;
                case 2:
                    menu_text = "Back";
                    break;
                }
                text.setPosition(textx, texty);
                text.setString(menu_text);
                window.draw(text);
                texty = texty + 38;
            }
        }
        if(option_level == 2)
        {
            //laat het graphics menu zien
            for(int i = 0; i <= options[0]; i++)
            {
                std::string menu_text;
                if(option_selected == i)
                {
                    text.setColor(sf::Color::White);
                }
                else
                {
                    text.setColor(sf::Color::Yellow);
                }
                switch(i)
                {
                case 0:
                    menu_text = "Graphics options: ";
                    break;
                case 1:
                    menu_text = "to be implanted";
                    break;
                case 2:
                    menu_text = "Back";
                    break;
                }
                text.setPosition(textx, texty);
                text.setString(menu_text);
                window.draw(text);
                texty = texty + 38;
            }
        }
        if(option_level == 3)
        {
            //laat het sound menu zien
            for(int i = 0; i <= options[0]; i++)
            {
                std::string menu_text;
                if(option_selected == i)
                {
                    text.setColor(sf::Color::White);
                }
                else
                {
                    text.setColor(sf::Color::Yellow);
                }
                switch(i)
                {
                case 0:
                    menu_text = "Sound options: ";
                    break;
                case 1:
                    menu_text = "to be implanted";
                    break;
                case 2:
                    menu_text = "Back";
                    break;
                }
                text.setPosition(textx, texty);
                text.setString(menu_text);
                window.draw(text);
                texty = texty + 38;
            }
        }
        texty = 20;
        text.setPosition(textx-80, texty);
        text.setCharacterSize(48);
        text.setColor(sf::Color::Green);
        text.setString("Testgame Menu");
        window.draw(text);
        texty = window_y-24;
        textx = window_x-136;
        text.setPosition(textx, texty);
        text.setCharacterSize(14);
        text.setColor(sf::Color::Red);
        text.setString("Aplha Build: 0.1.5");
        window.draw(text);
        window.display();
    }
}


