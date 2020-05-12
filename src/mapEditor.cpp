#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include "globals.h"

static int nMapArray[MAP_HEIGHT ][ MAP_WIDTH ] = {0};
static int nItemArray[ MAP_HEIGHT ][ MAP_WIDTH ] = {0};
static sf::Event event;
static sf::Sprite sItem_Potion, sItem_Rock, sItem_Key, sItem_Ship, sItem_Pickaxe, sTile_RockFloor, sTile_Wall, sTile_ClosedDoor, sTile_OpenDoor, sTile_Grass, sTile_Tree, sTile_LockedDoor,
splayer, sActor, sNPC,sTilePrev, sTileNext, sTileDungeon, sGameBackground, sItem_WoodenSword, sCrosshair, sItem_Bow, sItem_Arrow, sItem_Shield, sTileWater;
static sf::Texture Item_Potion, Item_Ship, TileWater0, TileWater1, TileWater2, TileWater3, Item_Rock, Item_Key, Item_Pickaxe, Tile_RockFloor, Tile_Wall, Tile_ClosedDoor, Tile_OpenDoor, Tile_Grass, Tile_Tree, Tile_LockedDoor,
tplayerUp, tplayerRight, tplayerDown, tplayerLeft, TilePrev, TileNext, TileDungeon, GameBackground, Item_WoodenSword, Crosshair, Item_Bow, Item_Arrow, Item_Shield;
static int player_position_x = 100;
static int player_position_y = 100;
static sf::Font font;
static sf::Text text;
static int porientation = 1;
static int real_map_width;
static int real_map_height;
static int NPC_Array[5][4] = {0};


static bool ispassable( int x, int y)
{
    if(x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
    {
        return false;
    }
    else
    {
        return true;
    }
}

static void DrawPlayer(int change_x, int change_y, float timepressed, float currentTime)
{
    float tempx, tempy;
    if(timepressed + 0.3 > currentTime)
    {
        switch (change_x)
        {
        case -1:
            tempx = player_position_x + 1 - (1*((currentTime-timepressed)/0.3));
            break;
        case 0:
            tempx = player_position_x;
            break;
        case 1:
            tempx = player_position_x -1 + (1*((currentTime-timepressed)/0.3));
            break;
        }
        switch (change_y)
        {
        case -1:
            tempy = player_position_y + 1 - (1*((currentTime-timepressed)/0.3));
            break;
        case 0:
            tempy = player_position_y;
            break;
        case 1:
            tempy = player_position_y - 1 + (1*((currentTime-timepressed)/0.3));
            break;
        }
        int tempx1 = tempx *32+16;
        int tempy1 = tempy *32+16;
        splayer.setPosition(tempx1, tempy1);
    }
    else
    {
        splayer.setPosition(player_position_x*32+16, player_position_y*32+16);
    }
    window.draw(splayer);
}

static void DrawMap( void )
{
    for( int y = 0; y < MAP_HEIGHT; y++ )
    {
        for( int x = 0; x < MAP_WIDTH; x++ )
        {
            switch (nMapArray[y][x])
            {
            case 0:
                sTile_RockFloor.setPosition(x*32, y*32);
                window.draw(sTile_RockFloor);
                break;
            case 1:
                sTile_Wall.setPosition(x*32, y*32);
                window.draw(sTile_Wall);
                break;
            case 2:
                sTile_ClosedDoor.setPosition(x*32, y*32);
                window.draw(sTile_ClosedDoor);
                break;
            case 3:
                sTile_OpenDoor.setPosition(x*32, y*32);
                window.draw(sTile_OpenDoor);
                break;
            case 4:
                sTile_Grass.setPosition(x*32, y*32);
                window.draw(sTile_Grass);
                break;
            case 5:
                sTile_Tree.setPosition(x*32, y*32);
                window.draw(sTile_Tree);
                break;
            case 6:
                sTile_LockedDoor.setPosition(x*32, y*32);
                window.draw(sTile_LockedDoor);
                break;
            case 7:
                sTileNext.setPosition(x*32, y*32);
                window.draw(sTileNext);
                break;
            case 8:
                sTilePrev.setPosition(x*32, y*32);
                window.draw(sTilePrev);
                break;
            case 9:
                sTileDungeon.setPosition(x*32, y*32);
                window.draw(sTileDungeon);
                break;
            case 10:
                sTileWater.setPosition(x*32, y*32);
                window.draw(sTileWater);
                break;
            }

        }
    }
}

static void DrawItems( void)
{
    for( int y = 0; y < MAP_HEIGHT; y++ )
    {
        for( int x = 0; x < MAP_WIDTH; x++ )
        {
            /*
            0 no item
            1 Potion
            2 Rock
            3 Key
            4 Pickaxe
            5 wooden sword
            */
            switch (nItemArray[y][x])
            {
            case 0:
                break;
            case 1:
                sItem_Potion.setPosition(x*32, y*32);
                window.draw(sItem_Potion);
                break;
            case 2:
                sItem_Rock.setPosition(x*32, y*32);
                window.draw(sItem_Rock);
                break;
            case 3:
                sItem_Key.setPosition(x*32, y*32);
                window.draw(sItem_Key);
                break;
            case 4:
                sItem_Pickaxe.setPosition(x*32, y*32);
                window.draw(sItem_Pickaxe);
                break;
            case 5:
                sItem_WoodenSword.setPosition(x*32, y*32);
                window.draw(sItem_WoodenSword);
                break;
            case 6:
                sItem_Bow.setPosition(x*32, y*32);
                window.draw(sItem_Bow);
                break;
            case 7:
                sItem_Arrow.setPosition(x*32, y*32);
                window.draw(sItem_Arrow);
                break;
            case 8:
                sItem_Shield.setPosition(x*32, y*32);
                window.draw(sItem_Shield);
                break;
            case 9:
                sItem_Ship.setPosition(x*32, y*32);
                window.draw(sItem_Ship);
                break;
            }

        }
    }
}

static void loadtextures()
{
    if(GameBackground.loadFromFile("Textures/background.png"))
    {
        sGameBackground.setTexture(GameBackground);
        sf::Vector2u bgsize = GameBackground.getSize();
        sGameBackground.scale((float) window_x/bgsize.x, (float) window_y/bgsize.y);
    }

    //items
    if(Item_Ship.loadFromFile("Textures/ship.png"))
    {
        sItem_Ship.setTexture(Item_Ship);
    }

    if(Item_Potion.loadFromFile("Textures/potion.png"))
    {
        sItem_Potion.setTexture(Item_Potion);
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
    //player sprites
    tplayerUp.loadFromFile("Textures/playerup.png");
    splayer.setTexture(tplayerUp);
    splayer.setOrigin( 16,16);
    sActor.setTexture(tplayerUp);
    sActor.setOrigin( 16,16);
    sNPC.setTexture(tplayerUp);
    sNPC.setOrigin( 16,16);
    sNPC.setColor(sf::Color::Green);
}

static int Watertexture(int watertile)
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

static void DrawItemList()
{
    if (!font.loadFromFile("fonts/TrajanPro-Regular.otf"))
    {
        // error...
    }
    text.setFont(font);
    text.setCharacterSize(round(item_list_y/1.5)*2);
    text.setColor(sf::Color::White);
    text.setString("Map Tiles");
    int textx = item_list_x, texty = item_list_y;
    text.setPosition(textx, texty);
    texty = item_list_y;
    window.draw(text);
    text.setCharacterSize(round(item_list_y/1.5));
    texty = texty + round(item_list_y/1.5)*2;
    text.setString("'0' = Rockfloor");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'1' = Wall");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'2' = Closed Door");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'3' = Open Door");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'4' = Grass");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'5' = Tree");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'6' = Locked Door");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'7' = Next Level");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'8' = Prev Level");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'9' = To dungeon");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'-' = Add water");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5)*2;
    text.setPosition(textx, texty);
    text.setCharacterSize(round(item_list_y/1.5)*2);
    text.setString("Place Items:");
    window.draw(text);
    text.setCharacterSize(round(item_list_y/1.5));
    texty = texty + round(item_list_y/1.5)*2;
    text.setString("'Q' = Potion");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'W' = Rock");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'E' = Key");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'R' = Pickaxe");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'T' = Wooden Sword");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'Y' = Bow");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'U' = Arrow");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'I' = Shield");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'O' = Boat");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'F' = Remove item");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5)*2;
    text.setPosition(textx, texty);
    text.setCharacterSize(round(item_list_y/1.5)*2);
    text.setString("Place NPC (max 5):");
    window.draw(text);
    text.setCharacterSize(round(item_list_y/1.5));
    texty = texty + round(item_list_y/1.5)*2;
    text.setString("'A' = Villager");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'Z' = Remove NPC");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5)*2;
    text.setPosition(textx, texty);
    text.setCharacterSize(round(item_list_y/1.5));
    text.setString("Save/Load");
    window.draw(text);
    text.setCharacterSize(round(item_list_y/1.5));
    texty = texty + round(item_list_y/1.5);
    text.setString("'S' = Save Map");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'A' = Save Map As (N/A)");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'D' = Load Map (N/A)");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5)*2;
    text.setString("'H' = Fill Rock");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'G' = Fill Tree");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5)*2;
    text.setString("Please note:");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("Saving as and loading from is not");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("supported at the moment. ");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("'maptest.txt' will be loaded");
    text.setPosition(textx, texty);
    window.draw(text);
    texty = texty + round(item_list_y/1.5);
    text.setString("at start and saved to at save");
    text.setPosition(textx, texty);
    window.draw(text);
}

static bool loadmap(std::string mapname)
{
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            nMapArray[i][j] = 5;
        }
    }
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            nItemArray[i][j] = 0;
        }
    }
    int number_of_lines = 0;
    int length_of_chars = 0;
    char cr;
    std::string org = mapname;
    mapname.append(".txt");
    real_map_width = 200;
    real_map_height = 200;
    std::ifstream mapfile (mapname.c_str());
    for (int i=0; i<real_map_height; ++i)
    {
        for (int j=0; j<real_map_width; ++j)
        {
            mapfile >> nMapArray[i][j];
        }
    }
    for (int i=0; i<real_map_height; ++i)
    {
        for (int j=0; j<real_map_width; ++j)
        {
            mapfile >> nItemArray[i][j];
        }
    }
    for (int i=0; i<5; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            mapfile >> NPC_Array[i][j];
        }
    }
    mapfile.close();
    return true;
}


static void fillempty(int tile)
{
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            if(nMapArray[i][j] == 5 || nMapArray[i][j] == 1)
            {
                nMapArray[i][j] = tile;
            }
        }
    }
}

static void SaveFile()
{
    std::string filename = "maps/maptest.txt";
    std::ofstream myfile(filename.c_str(), std::ios::out);
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            myfile << nMapArray[i][j];
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
            myfile << nItemArray[i][j];
            if(j < MAP_WIDTH-1)
            {
                myfile << " ";
            }
        }
        myfile <<"\n";
    }
    for (int i=0; i<5; ++i)
    {
        myfile << NPC_Array[i][0] << " " << NPC_Array[i][1] << " "<< NPC_Array[i][2]<< " " << NPC_Array[i][3] << "\n";
    }
    myfile.close();
}

static void move_view(int change_x, int change_y, float currentTime, float timepressed,  float timepressed_x, float timepressed_y)
{
    float tempx, tempy;
    if(timepressed + 0.3 > currentTime)
    {
        if(timepressed_x + 0.3 > currentTime)
        {
            switch (change_x)
            {
            case -1:
                tempx = player_position_x + 1 - (1*((currentTime-timepressed_x)/0.3));
                break;
            case 0:
                tempx = player_position_x;
                break;
            case 1:
                tempx = player_position_x -1 + (1*((currentTime-timepressed_x)/0.3));
                break;
            }
        }
        else
        {
            tempx = player_position_x;
        }
        if(timepressed_y + 0.3 > currentTime)
        {
            switch (change_y)
            {
            case -1:
                tempy = player_position_y + 1 - (1*((currentTime-timepressed_y)/0.3));
                break;
            case 0:
                tempy = player_position_y;
                break;
            case 1:
                tempy = player_position_y - 1 + (1*((currentTime-timepressed_y)/0.3));
                break;
            }
        }
        else
        {
            tempy = player_position_y;
        }
        int tempx1 = tempx *32;
        int tempy1 = tempy *32;
        view1.reset(sf::FloatRect(tempx1-(viewport_x/2), tempy1-(viewport_y/2), viewport_x, viewport_y));
    }
    else
    {
        view1.reset(sf::FloatRect((player_position_x*32)-(viewport_x/2), (player_position_y*32)-(viewport_y/2), viewport_x, viewport_y));
    }
}

static void DrawNPCs()
{
    for(int i = 0; i <5; i++)
    {
        if(NPC_Array[i][3] != 0)
        {
            sNPC.setPosition(NPC_Array[i][0]*32+16, NPC_Array[i][1]*32+16);
            window.draw(sNPC);
        }
    }
}

int mapEditor()
{
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            nMapArray[i][j] = 5;
        }
    }
    loadmap("maps/maptest");
    sf::Clock clockMain;
    float timepressed = 0;
    float timepressed_x = 0;
    float timepressed_y = 0;
    window.setFramerateLimit(60);
    view1.setViewport(sf::FloatRect(0, 0, 0.8f, 0.8f));
    loadtextures();
    splayer.setPosition(0, 0);
    int change_x = 0, change_y = 0;
    bool focus = true;
    int watertile = 0;
    float water = 0;
    while(window.isOpen())
    {
        sf::Time elapsedMain = clockMain.getElapsedTime();
        window.clear();
        if((timepressed + 0.3) < elapsedMain.asSeconds())
        {
            change_x = 0;
            change_y = 0;
        }
        while (window.pollEvent(event))
        {
            switch(event.type)
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
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                case sf::Keyboard::Escape:
                    return 0;
                    break;
                }
                break;
            }
        }
        if(focus == true)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (timepressed_y + 0.3) < elapsedMain.asSeconds())
            {
                porientation = 1;
                splayer.setRotation(0);
                timepressed = elapsedMain.asSeconds();
                timepressed_y = elapsedMain.asSeconds();
                if(ispassable(player_position_x, player_position_y - 1))
                {
                    player_position_y = player_position_y - 1;
                    change_y = -1;
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (timepressed_y + 0.3) < elapsedMain.asSeconds())
            {
                porientation = 2;
                splayer.setRotation(180);
                timepressed = elapsedMain.asSeconds();
                timepressed_y = elapsedMain.asSeconds();
                if(ispassable(player_position_x, player_position_y + 1) == true)
                {
                    player_position_y = player_position_y + 1;
                    change_y = 1;
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (timepressed_x + 0.3) < elapsedMain.asSeconds())
            {
                porientation = 3;
                splayer.setRotation(90);
                timepressed = elapsedMain.asSeconds();
                timepressed_x = elapsedMain.asSeconds();
                if(ispassable(player_position_x+1, player_position_y))
                {
                    player_position_x = player_position_x + 1;
                    change_x = 1;
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (timepressed_x + 0.3) < elapsedMain.asSeconds())
            {
                porientation = 4;
                splayer.setRotation(270);
                timepressed = elapsedMain.asSeconds();
                timepressed_x = elapsedMain.asSeconds();
                if(ispassable(player_position_x-1, player_position_y))
                {
                    player_position_x = player_position_x - 1;
                    change_x = -1;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
            {
                nMapArray[player_position_y][player_position_x] = 0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                nMapArray[player_position_y][player_position_x] = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                nMapArray[player_position_y][player_position_x] = 2;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                nMapArray[player_position_y][player_position_x] = 3;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                nMapArray[player_position_y][player_position_x] = 4;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            {
                nMapArray[player_position_y][player_position_x] = 5;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
            {
                nMapArray[player_position_y][player_position_x] = 6;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
            {
                nMapArray[player_position_y][player_position_x] = 7;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
            {
                nMapArray[player_position_y][player_position_x] = 8;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
            {
                nMapArray[player_position_y][player_position_x] = 9;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
            {
                nMapArray[player_position_y][player_position_x] = 10;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                nItemArray[player_position_y][player_position_x] = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                nItemArray[player_position_y][player_position_x] = 2;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                nItemArray[player_position_y][player_position_x] = 3;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                nItemArray[player_position_y][player_position_x] = 4;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
            {
                nItemArray[player_position_y][player_position_x] = 5;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
            {
                nItemArray[player_position_y][player_position_x] = 6;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::U))
            {
                nItemArray[player_position_y][player_position_x] = 7;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            {
                nItemArray[player_position_y][player_position_x] = 8;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
            {
                nItemArray[player_position_y][player_position_x] = 9;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                nItemArray[player_position_y][player_position_x] = 0;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                SaveFile();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                loadmap("maps/maptest");
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            {
                fillempty(1);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            {
                fillempty(5);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                bool placed = false;
                for(int j = 0; j <5; j++)
                {
                    if(NPC_Array[j][0] == player_position_x && NPC_Array[j][1] == player_position_y )
                    {
                        placed = true;
                    }
                }
                int i = 0;
                while( i < 5)
                {
                    if(placed == false)
                    {
                        if(NPC_Array[i][3] == 0)
                        {
                            NPC_Array[i][0] = player_position_x;
                            NPC_Array[i][1] = player_position_y;
                            NPC_Array[i][2] = 0;
                            NPC_Array[i][3] = 1;
                            placed = true;
                        }
                    }
                    i = i +1;
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                for(int j = 0; j <5; j++)
                {
                    if(NPC_Array[j][0] == player_position_x && NPC_Array[j][1] == player_position_y )
                    {
                        NPC_Array[j][0] = 0;
                        NPC_Array[j][1] = 0;
                        NPC_Array[j][2] = 0;
                        NPC_Array[j][3] = 0;
                    }
                }
            }
        }
        float currentTime = elapsedMain.asSeconds();
        move_view(change_x, change_y, currentTime, timepressed, timepressed_x, timepressed_y);
        if(currentTime > water + 0.3)
        {
            water = currentTime;
            watertile = Watertexture(watertile);
        }
        window.setView(totalview);
        window.draw(sGameBackground);
        window.setView(view1);
        DrawMap();
        DrawItems();
        DrawNPCs();
        DrawPlayer(change_x, change_y, timepressed, elapsedMain.asSeconds());
        window.setView(window.getDefaultView());
        DrawItemList();
        window.display();
    }
}
