#ifndef PLAYER_H
#define PLAYER_H


class Player_State
{

public:
    bool positionHasUpdated = false;
    int position_x = 4;
    int position_y = 4;
    int porientation = 1;
    int nInventory[10] = {0};
    int aInventory[10] = {0};
    int Lvl = 1;
    int Experience = 1;
    float health = 100;
    int max_health = 100;
    int max_mana = 100;
    float mana = 100;
    int magic_attack = 25;
    int attack = 10;
    float armor = 10;
    int Gold = 0;
    void OrientPlayer( float timepressed_x, float timepressed_y, float timepressed_up, float timepressed_down, float timepressed_left, float timepressed_right, float currentTime);
    void DrawPlayer(int change_x, int change_y, float timepressed, float currentTime);
    void DropItem();
    void UseItem();
    void UseDoor();
    bool boardShip(bool inBoat);
    void died();
    void Do_Attack();
    void Do_Magic_Attack();
    int Pick_Up_Item();
    void Shoot_Arrow(float gametime);
    void Talk(float currenttime);
    void Level_up();



protected:




};

extern Player_State Player;

#endif // PLAYER_H
