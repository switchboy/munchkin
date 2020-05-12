#include <fstream>
#include "gamemap.h"
#include "actors.h"
#include "npc.h"
#include "itemshop.h"
#include "gameengine.h"
#include "player.h"

Game_Map current_map;

bool Game_Map::ispassable( int x, int y, bool bow, bool boat)
{
    if(x < 0 || y < 0 || x >= real_map_width || y >= real_map_height)
    {
        return false;
    }
    else
    {
        int nTileValue = nMapArray[y][x];
        if(tileproperties[nTileValue] == 1)
        {
            if(bow == true || nOccupied[y][x] == 0 )
            {
                if(bow == true && boat == true )
                {
                    return true;
                }
                if(bow == false && boat == true)
                {
                    return false;
                }
                if(bow == false && boat == false)
                {
                    return true;
                }
                if(bow == true && boat == false)
                {
                    return true;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(tileproperties[nTileValue] == 2 )
            {
                if(bow == true || boat == true)
                {
                    return true;
                }
            }
            return false;
        }
    }
}

bool Game_Map::loadmap(std::string mapname)
{
    minimapTextureExist = false;
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            nMapArray[i][j] = 0;
        }
    }
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            nItemArray[i][j] = 0;
        }
    }
    for (int i=0; i<MAP_HEIGHT; ++i)
    {
        for (int j=0; j<MAP_WIDTH; ++j)
        {
            nOccupied[i][j] = 0;
        }
    }
    for( int i = 0; i < MAX_ACTORS; i++ )
    {
        p_cActorList[i] = NULL;
    }
    for( int i = 0; i < 5; i++ )
    {
        p_cfriendly_npcList[i] = NULL;
    }
    for( int i = 0; i < 5; i++ )
    {
        itemShopList[i] = NULL;
    }
    Game.mapname_name = "maps/"+mapname;
    mapname.append(".txt");
    real_map_width = 200;
    real_map_height = 200;
    int npc_var[5][4];
    int shop_var[5][4];
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
            mapfile >> npc_var[i][j];
        }
    }
    for (int i=0; i<5; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            mapfile >> shop_var[i][j];
        }
    }

    mapfile.close();
    if(!Game.dungeon)
    {
        for( int i = 0; i < enemies[0][Game.mapnr]; i++ )
        {
            int x, y;
            Actor *p_cNewActor = new Actor();
            do
            {
                x = rand() % real_map_width;
                y = rand() % real_map_height;
            }
            while( !ispassable(x,y, false, false) );
            p_cNewActor->SetPos( x, y, 100 );
            AddActorToList( p_cNewActor );
        }
        Game.current_actors = enemies[0][Game.mapnr];
    }
    else
    {
        for( int i = 0; i < enemies[1][Game.mapnr]; i++ )
        {
            int x, y;
            Actor *p_cNewActor = new Actor();
            do
            {
                x = rand() % real_map_width;
                y = rand() % real_map_height;
            }
            while( !ispassable(x,y, false, false) );
            p_cNewActor->SetPos( x, y, 100 );
            AddActorToList( p_cNewActor );
        }
        Game.current_actors = enemies[1][Game.mapnr];
    }
    for (int i=0; i<5; ++i)
    {
        if(npc_var[i][3] == 1)
        {
            friendly_npc *p_cfriendly_npc = new friendly_npc();
            p_cfriendly_npc->SetPos( npc_var[i][0], npc_var[i][1]);
            p_cfriendly_npc->SetType( npc_var[i][2]);
            nOccupied[npc_var[i][1]][npc_var[i][0]] = 1;
            AddNPCToList( p_cfriendly_npc );
        }
    }
    for (int i=0; i<5; ++i)
    {
        if(shop_var[i][3] == 1)
        {
            itemShop *nItemShop = new itemShop();
            nItemShop->setShopPosition(shop_var[i][0], shop_var[i][1]);
            nItemShop->setShopType(shop_var[i][2]);
            nOccupied[shop_var[i][1]][shop_var[i][0]] = 1;
            nOccupied[shop_var[i][1]+1][shop_var[i][0]] = 1;
            nOccupied[shop_var[i][1]+1][shop_var[i][0]+1] = 1;
            nOccupied[shop_var[i][1]][shop_var[i][0]+1] = 1;
            addItemShop( nItemShop );
        }
    }
    return true;
}


void Game_Map::DrawMap( void )
{
    visible_y = (window_y * 0.8)/32;
    int low_limit_x, upper_limit_x, low_limit_y, upper_limit_y;
    low_limit_x = (Player.position_x - (visible_x/2))-2;
    if(low_limit_x < 0)
    {
        low_limit_x = 0;
    }
    upper_limit_x = (Player.position_x + (visible_x/2))+2;
    if(upper_limit_x > MAP_WIDTH)
    {
        upper_limit_x = MAP_WIDTH;
    }
    low_limit_y = (Player.position_y - (visible_y/2))-2;
    if(low_limit_y < 0)
    {
        low_limit_y = 0;
    }
    upper_limit_y = (Player.position_y + (visible_y/2))+2;
    if(upper_limit_y > MAP_HEIGHT)
    {
        upper_limit_y = MAP_HEIGHT;
    }
    for( int y = low_limit_y; y < upper_limit_y; y++ )
    {
        for( int x = low_limit_x; x < upper_limit_x; x++ )
        {
            switch (nMapArray[y][x])
            {
            case 0:
                Game.sTile_RockFloor.setPosition(x*32, y*32);
                window.draw(Game.sTile_RockFloor);
                break;
            case 1:
                Game.sTile_Wall.setPosition(x*32, y*32);
                window.draw(Game.sTile_Wall);
                break;
            case 2:
                Game.sTile_ClosedDoor.setPosition(x*32, y*32);
                window.draw(Game.sTile_ClosedDoor);
                break;
            case 3:
                Game.sTile_OpenDoor.setPosition(x*32, y*32);
                window.draw(Game.sTile_OpenDoor);
                break;
            case 4:
                Game.sTile_Grass.setPosition(x*32, y*32);
                window.draw(Game.sTile_Grass);
                break;
            case 5:
                Game.sTile_Tree.setPosition(x*32, y*32);
                window.draw(Game.sTile_Tree);
                break;
            case 6:
                Game.sTile_LockedDoor.setPosition(x*32, y*32);
                window.draw(Game.sTile_LockedDoor);
                break;
            case 7:
                Game.sTileNext.setPosition(x*32, y*32);
                window.draw(Game.sTileNext);
                break;
            case 8:
                Game.sTilePrev.setPosition(x*32, y*32);
                window.draw(Game.sTilePrev);
                break;
            case 9:
                Game.sTileDungeon.setPosition(x*32, y*32);
                window.draw(Game.sTileDungeon);
                break;
            case 10:
                Game.sTileWater.setPosition(x*32, y*32);
                window.draw(Game.sTileWater);
                break;
            }

        }
    }
    for(int i = 0; i < 5; i++ )
    {
        if(itemShopList[i] != NULL )
        {
            itemShopList[i]->drawShop();
        }
    }
}

void Game_Map::drawMiniMap()
{
    if(!minimapTextureExist)
    {
        minimapTexture.create(800,800);
        minimapTexture.clear();
        int low_limit_x, upper_limit_x, low_limit_y, upper_limit_y;
        low_limit_x = 0;
        upper_limit_x = MAP_WIDTH;
        low_limit_y = 0;
        upper_limit_y = MAP_HEIGHT;
        int xMinimapTile = 4;
        int yMinimapTile = 4;
        sf::RectangleShape miniMapPixel(sf::Vector2f(xMinimapTile, yMinimapTile));
        for( int y = low_limit_y; y < upper_limit_y; y++ )
        {
            for( int x = low_limit_x; x < upper_limit_x; x++ )
            {
                switch (nMapArray[y][x])
                {
                case 0:
                    miniMapPixel.setFillColor(sf::Color(250, 150, 100));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 1:
                    miniMapPixel.setFillColor(sf::Color(103, 56, 6));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 2:
                    miniMapPixel.setFillColor(sf::Color(56, 47, 37));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 3:
                    miniMapPixel.setFillColor(sf::Color(203, 180, 155));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 4:
                    miniMapPixel.setFillColor(sf::Color(68, 154, 51));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 5:
                    miniMapPixel.setFillColor(sf::Color(14, 60, 5));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 6:
                    miniMapPixel.setFillColor(sf::Color(0, 0, 0));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 7:
                    miniMapPixel.setFillColor(sf::Color(255, 255, 255));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 8:
                    miniMapPixel.setFillColor(sf::Color(255, 255, 255));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 9:
                    miniMapPixel.setFillColor(sf::Color(255, 0, 0));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                case 10:
                    miniMapPixel.setFillColor(sf::Color(0, 162, 255));
                    miniMapPixel.setPosition(x*xMinimapTile,y*yMinimapTile);
                    minimapTexture.draw(miniMapPixel);
                    break;
                }
            }
        }
        minimapTexture.display();
        minimapTextureExist = true;
    }
    sf::Sprite miniMapBackground;
    miniMapBackground.setTexture(minimapTexture.getTexture());
    miniMapBackground.scale((float) minimap_x/800, (float) minimap_y/800);
    window.setView(minimap);
    window.draw(miniMapBackground);
    //teken de view in de minimap
    sf::RenderTexture minimapTextureActors;
    minimapTextureActors.create(800,800);
    minimapTextureActors.clear(sf::Color(0,0,0,0));
    sf::CircleShape minimapPlayer(4);
    minimapPlayer.setFillColor(sf::Color(8, 88, 168));
    minimapPlayer.setPosition(Player.position_x*4, Player.position_y*4);
    minimapTextureActors.draw(minimapPlayer);
    minimapPlayer.setFillColor(sf::Color(234, 2, 255));
    for(int i = 0; i <5; i++ )
    {
        if(itemShopList[i] != NULL)
        {
            minimapPlayer.setPosition(itemShopList[i]->getShopLocationX()*4, itemShopList[i]->getShopLocationY()*4);
            minimapTextureActors.draw(minimapPlayer);
        }

    }
    minimapPlayer.setFillColor(sf::Color(255, 255, 0));
    for(int i = 0; i <5; i++ )
    {
        if(p_cfriendly_npcList[i] != NULL)
        {
            minimapPlayer.setPosition(p_cfriendly_npcList[i]->getNPCLocationX()*4, p_cfriendly_npcList[i]->getNPCLocationY()*4);
            minimapTextureActors.draw(minimapPlayer);
        }

    }
    minimapPlayer.setFillColor(sf::Color(120, 0, 0));
    for(int i = 0; i < MAX_ACTORS; i++ )
    {
        if(p_cActorList[i] != NULL)
        {
            minimapPlayer.setPosition(p_cActorList[i]->getActorLocationX()*4, p_cActorList[i]->getActorLocationY()*4);
            minimapTextureActors.draw(minimapPlayer);
        }

    }
    sf::RectangleShape viewBox(sf::Vector2f(visible_x, visible_y));
    viewBox.setFillColor(sf::Color(0,0,0,0));
    viewBox.setOutlineThickness(4.f);
    viewBox.setOutlineColor(sf::Color(255,255,255));
    viewBox.setOrigin(sf::Vector2f(visible_x/2, visible_y/2));
    viewBox.setPosition(Player.position_x*4,Player.position_y*4);
    minimapTextureActors.draw(viewBox);
    minimapTextureActors.display();
    sf::Sprite miniMapForeground;
    miniMapForeground.setTexture(minimapTextureActors.getTexture());
    miniMapForeground.scale((float) minimap_x/800, (float) minimap_y/800);
    window.draw(miniMapForeground);
}

void Game_Map::DrawItems( void)
{
    viewport_y = window_y * 0.8;
    visible_y = viewport_y/32;
    int low_limit_x, upper_limit_x, low_limit_y, upper_limit_y;
    low_limit_x = (Player.position_x - (visible_x/2))-1;
    if(low_limit_x < 0)
    {
        low_limit_x = 0;
    }
    upper_limit_x = (Player.position_x + (visible_x/2))+1;
    if(upper_limit_x > real_map_width)
    {
        upper_limit_x = real_map_width;
    }
    low_limit_y = (Player.position_y - (visible_y/2))-1;
    if(low_limit_y < 0)
    {
        low_limit_y = 0;
    }
    upper_limit_y = (Player.position_y + (visible_y/2))+1;
    if(upper_limit_y > real_map_height)
    {
        upper_limit_y = real_map_height;
    }
    for( int y = low_limit_y; y < upper_limit_y; y++ )
    {
        for( int x = low_limit_x; x < upper_limit_x; x++ )
        {
            switch (nItemArray[y][x])
            {
            case 0:
                break;
            case 1:
                Game.sItem_Potion.setPosition(x*32, y*32);
                window.draw(Game.sItem_Potion);
                break;
            case 2:
                Game.sItem_Rock.setPosition(x*32, y*32);
                window.draw(Game.sItem_Rock);
                break;
            case 3:
                Game.sItem_Key.setPosition(x*32, y*32);
                window.draw(Game.sItem_Key);
                break;
            case 4:
                Game.sItem_Pickaxe.setPosition(x*32, y*32);
                window.draw(Game.sItem_Pickaxe);
                break;
            case 5:
                Game.sItem_WoodenSword.setPosition(x*32, y*32);
                window.draw(Game.sItem_WoodenSword);
                break;
            case 6:
                Game.sItem_Bow.setPosition(x*32, y*32);
                window.draw(Game.sItem_Bow);
                break;
            case 7:
                Game.sItem_Arrow.setPosition(x*32, y*32);
                window.draw(Game.sItem_Arrow);
                break;
            case 8:
                Game.sItem_Shield.setPosition(x*32, y*32);
                window.draw(Game.sItem_Shield);
                break;
            case 9:
                Game.sItem_Ship.setPosition(x*32, y*32);
                window.draw(Game.sItem_Ship);
                break;
            case 10:
                Game.sItem_ManaPotion.setPosition(x*32, y*32);
                window.draw(Game.sItem_ManaPotion);
                break;
            }

        }
    }
}

void Game_Map::spwan_location(int next)
{
    int gelukt = 0;
    for(int i = 0; i < MAP_HEIGHT; i++ )
    {
        for(int j =0; j <MAP_WIDTH; j++)
        {
            if(nMapArray[i][j] == 7 && next ==0)
            {
                gelukt = 1;
                if(ispassable(j, i+1, false, false))
                {
                    Player.position_x = j;
                    Player.position_y = i+1;
                }
                else if(ispassable(j, i-1, false, false))
                {
                    Player.position_x = j;
                    Player.position_y = i-1;
                }
                else if(ispassable(j+1, i, false, false))
                {
                    Player.position_x = j+1;
                    Player.position_y = i;
                }
                else if(ispassable(j-1, i, false, false))
                {
                    Player.position_x = j-1;
                    Player.position_y = i;
                }
                else
                {
                    Player.position_x = 1;
                    Player.position_y = 1;
                }
            }
            else if(nMapArray[i][j] == 8 && next ==1)
            {
                gelukt = 1;
                if(ispassable(j, i+1, false, false))
                {
                    Player.position_x = j;
                    Player.position_y = i+1;
                }
                else if(ispassable(j, i-1, false, false))
                {
                    Player.position_x = j;
                    Player.position_y = i-1;
                }
                else if(ispassable(j+1, i, false, false))
                {
                    Player.position_x = j+1;
                    Player.position_y = i;
                }
                else if(ispassable(j-1, i, false, false))
                {
                    Player.position_x = j-1;
                    Player.position_y = i;
                }
                else
                {
                    Player.position_x = 1;
                    Player.position_y = 1;
                }
            }
            else if(nMapArray[i][j] == 9 && next ==2)
            {
                gelukt = 1;
                if(ispassable(j, i+1, false, false))
                {
                    Player.position_x = j;
                    Player.position_y = i+1;
                }
                else if(ispassable(j, i-1, false, false))
                {
                    Player.position_x = j;
                    Player.position_y = i-1;
                }
                else if(ispassable(j+1, i, false, false))
                {
                    Player.position_x = j+1;
                    Player.position_y = i;
                }
                else if(ispassable(j-1, i, false, false))
                {
                    Player.position_x = j-1;
                    Player.position_y = i;
                }
                else
                {
                    Player.position_x = 1;
                    Player.position_y = 1;
                }
            }
        }
    }
    if(gelukt == 0)
    {
        Player.position_x = 1;
        Player.position_y = 1;
    }
}
