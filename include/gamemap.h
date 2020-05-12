#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "globals.h"

class Game_Map
{

public:

    int nMapArray[ MAP_HEIGHT ][ MAP_WIDTH ];
    int nItemArray[ MAP_HEIGHT ][ MAP_WIDTH ];
    int nOccupied[ MAP_HEIGHT ][ MAP_WIDTH ];
    int tileproperties[11] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 2};
    int nItemDMG[11] = {0, 0, 1, 0, 2, 3, 0, 1, 0, 0, 0};
    int nItemARM[11] = {0, 1, 0, 0, 0, 0, 0, 0, 15, 0, 0};
    void DrawMap(void);
    void DrawItems(void);
    bool loadmap(std::string mapname);
    bool ispassable( int x, int y, bool bow, bool boat);
    void spwan_location(int next);
    int real_map_width = 0;
    int real_map_height = 0;
    void drawMiniMap();

protected:


};
extern Game_Map current_map;

#endif // GAMEMAP_H
