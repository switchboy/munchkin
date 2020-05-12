#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "globals.h"

class Game_Engine
{

public:
    int current_actors = 0;
    int mapnr = 1;
    int highest_level = mapnr;
    int dungeon_visited[99] = {0};
    int gametext = 0;
    bool dungeon = false;
    sf::Font font;
    sf::Text text;
    sf::Event event;

    sf::Sprite  sItem_PotionShop, sItem_RockShop, sItem_KeyShop, sItem_ShipShop, sItem_PickaxeShop, sItem_WoodenSwordShop, sItem_BowShop, sItem_ArrowShop, sItem_ShieldShop, sItem_ManaPotion, sItem_ManaPotionShop,
    sItem_Potion, sItem_Rock, sItem_Key, sItem_Ship, sItem_Pickaxe, sTile_RockFloor, sTile_Wall, sTile_ClosedDoor, sTile_OpenDoor, sTile_Grass, sTile_Tree, sTile_LockedDoor,
    splayer, sActor, sNPC,sTilePrev, sTileNext, sTileDungeon, sGameBackground, sItem_WoodenSword, sCrosshair, sItem_Bow, sItem_Arrow, sItem_Shield, sTileWater, sShop;

    sf::Texture Item_PotionShop, Item_ShipShop, Item_RockShop, Item_KeyShop, Item_PickaxeShop,  Item_WoodenSwordShop, Item_BowShop, Item_ArrowShop, Item_ShieldShop, playerInBoat, Item_ManaPotion, Item_ManaPotionShop,
    Item_Potion, Item_Ship, TileWater0, TileWater1, TileWater2, TileWater3, Item_Rock, Item_Key, Item_Pickaxe, Tile_RockFloor, Tile_Wall, Tile_ClosedDoor, Tile_OpenDoor,
    Tile_Grass, Tile_Tree, Tile_LockedDoor, tplayerUp, tNPC, tplayerRight, tplayerDown, tplayerLeft, TilePrev, TileNext, TileDungeon, GameBackground, Item_WoodenSword,
    Crosshair, Item_Bow, Item_Arrow, Item_Shield, tActor, tShop;

    std::string mapname_name = "map1";
    void loadtextures();
    void DrawItemList(int shop);
    void Gametext(sf::String detext);
    void save_state(std::string mapname);
    void move_view(int change_x, int change_y, float currentTime, float timepressed,  float timepressed_x, float timepressed_y);
    int load_prev_level();
    int load_next_level();
    int switch_dungeon();
    void Initialize();
    void menu();
    int Watertexture(int watertile);
    int getMapNumber();
    bool getDungeon();
    std::string itemNameList[12] = {"Nothing", "Potion", "Rock", "Key", "Pickaxe", "Wooden Sword", "Bow", "Arrow", "Shield", "Boat", "Mana Potion"};
    int itemPriceList[12] = {0, 500, 10, 9999, 1200, 2800, 3600, 100, 5000, 9999, 500};

protected:
    bool game_in_progress = false;


};
extern Game_Engine Game;

#endif // GAMEENGINE_H
