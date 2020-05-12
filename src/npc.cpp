#include "npc.h"
#include "globals.h"
#include "gameengine.h"
#include "player.h"
#include "gamemap.h"


friendly_npc *	p_cfriendly_npcList [ 5 ];
bool AddNPCToList( friendly_npc *p_cfriendly_npc );
bool RemoveActorFromList( friendly_npc *p_cfriendly_npc );

friendly_npc::friendly_npc(void)
{
    this->nPosX = 0;
    this->nPosY = 0;
    this->oPosX = 0;
    this->oPosY = 0;
    this->npc_kind = 0;
    this->lastupdate = 0;

}
int friendly_npc::getValue( int value)
{
    if(value == 0)
    {
        return this->nPosX;
    }
    else if(value == 1)
    {
        return this->nPosY;
    }
    else if(value == 2)
    {
        return this->npc_kind;
    }
    else
    {
        return 0;
    }
}

void friendly_npc::SetType(int type)
{
    this->npc_kind = type;
}

void friendly_npc::SetId(int id)
{
    this->npcId = id;
}

void friendly_npc::SetPos( int x, int y)
{
    if( (x < 0) || (x >= MAP_WIDTH) ||
            (y< 0) || (y >= MAP_HEIGHT ) )
        return;

    this->oPosX= x;
    this->oPosY = y;
    this->nPosX= x;
    this->nPosY = y;
}

void friendly_npc::draw(float currenttime)
{
    float plh = 100;
    float hbx = (plh/100)*32;
    sf::RectangleShape health_bar_front;
    sf::RectangleShape health_bar_background;
    health_bar_background.setSize(sf::Vector2f( 8, 8 ));
    health_bar_front.setSize(sf::Vector2f(8, 8 ));
    health_bar_background.setOutlineThickness(1);
    health_bar_background.setOutlineColor(sf::Color::Black);
    health_bar_background.setFillColor(sf::Color::Red);
    health_bar_front.setFillColor(sf::Color::Yellow);
    if( (this->nPosX < 0) || (this->nPosX >= MAP_WIDTH) ||
            (this->nPosY < 0) || (this->nPosY >= MAP_HEIGHT ) )
        return;

    //Game.sActor.setColor(sf::Color::Red);
    float tempx, tempy;
    if(this->lastupdate + 0.3 > currenttime)
    {
        int change_x = this->nPosX - this->oPosX;
        int change_y = this->nPosY - this->oPosY;
        switch (change_x)
        {
        case -1:
            tempx = this->nPosX + 1 - (1*((currenttime-this->lastupdate)/0.3));
            break;
        case 0:
            tempx = this->nPosX;
            break;
        case 1:
            tempx = this->nPosX -1 + (1*((currenttime-this->lastupdate)/0.3));
            break;
        }
        switch (change_y)
        {
        case -1:
            tempy = this->nPosY + 1 - (1*((currenttime-this->lastupdate)/0.3));
            break;
        case 0:
            tempy = this->nPosY;
            break;
        case 1:
            tempy = this->nPosY - 1 + (1*((currenttime-this->lastupdate)/0.3));
            break;
        }
        int tempx1 = tempx *32+16;
        int tempy1 = tempy *32+16;
        Game.sNPC.setPosition(tempx1, tempy1);
    }
    else
    {
        Game.sNPC.setPosition(this->nPosX*32+16, this->nPosY*32+16);
        health_bar_background.setPosition(this->nPosX*32+12, this->nPosY*32-14);
        health_bar_front.setPosition(this->nPosX*32+12, this->nPosY*32-14);
    }
    window.draw(Game.sNPC);
    if(this->awareOfPlayer)
    {
        window.draw(health_bar_background);
        window.draw(health_bar_front);
    }
}



/*
int random = rand() % 2;
switch (random){
    case 0:
        gametext = "Lovely weather isn't it?";
        break;
    case 1:
        gametext = "I've heard there are many dangerous thoughs in the forrest!";
        break;
    case 2:
        gametext = "Did you know you can use a potion to heal yourself?";
        break;
    case 3:
        gametext = "To shoot a bow you'll need arrows!";
        break;
    case 4:
        gametext = "You can unlock locked doors with keys!";
        break;
    case 5:
        gametext = "Some items automaticly increase your damage...";
        break;
    case 6:
        gametext = "Some items automaticly increase your armour...";
        break;
    case 7:
        gametext = "If you carry a magic scroll you'll do more magic damage.";
        break;
    case 8:
        gametext = "Some area's have a hidden dungeon!";
        break;
    case 9:
        gametext = "Be carefull the forest can be a dangerous place!";
        break;
    case 10:
        gametext = "I think I am lost...";
        break;
    case 11:
        gametext = "I once was a warrior, but I took an arrow to the knee.";
        break;
    */


/*

    */

std::string friendly_npc::interact_npc(int pos_x, int pos_y, float currenttime)
{
    std::string gametext;
    if(pos_x == this->nPosX && pos_y == this->nPosY)
    {
        switch(Game.getMapNumber())
        {
        case 1:
            if(Game.getDungeon())
            {
                //Dungeon NPC interactions
                switch (this->npcId)
                {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                }
            }
            else
            {
                //Overworld interactions
                switch (this->npcId)
                {
                case 0:
                    Game.Gametext("You can unlock locked doors with keys!");
                    break;
                case 1:
                    Game.Gametext("To shoot a bow you'll need arrows!");
                    break;
                case 2:
                    Game.Gametext("Did you know you can use a potion to heal yourself?");
                    break;
                case 3:
                    Game.Gametext("Be carefull the forest can be a dangerous place!");
                    break;
                case 4:
                    Game.Gametext("I once was a warrior, but I took an arrow to the knee.");
                    break;
                }
            }
            break;

        default:
            break;
        }
    }
    return gametext;
}


void friendly_npc::update_npc( float currenttime )
{
    //check if player is nearby
    float distanceXToPlayer = Player.position_x - nPosX;
    float distanceYToPlayer = Player.position_y - nPosY;
    float pyDistance = sqrtf(distanceXToPlayer*distanceXToPlayer + distanceYToPlayer*distanceYToPlayer);
    if(pyDistance <= 4)
    {
        this->awareOfPlayer = true;
    }
    if(this->lastupdate + 2 < currenttime)
    {
        int iDeltaX;
        int iDeltaY;
        // Generate a new set of deltas for this actor
        if(pyDistance > 4)
        {
            this->awareOfPlayer = false;
            iDeltaX = (rand() % 3) - 1;
            iDeltaY = (rand() % 3) - 1;
            int tries = 0;
            while(!friendly_npc::changePositionIfAvailable(iDeltaX, iDeltaY, currenttime) && tries < 8)
            {
                iDeltaX = (rand() % 3) - 1;
                iDeltaY = (rand() % 3) - 1;
                tries++;
            }
        }
        else
        {
            this->awareOfPlayer = true;
        }
    }
}

bool friendly_npc::changePositionIfAvailable(int iDeltaX, int iDeltaY, float currenttime)
{
    if( current_map.ispassable(this->nPosX+iDeltaX, this->nPosY+iDeltaY, false, false) )
    {
        current_map.nOccupied[nPosY][nPosX] = 0;
        this->oPosX = nPosX;
        this->oPosY = nPosY;
        this->nPosX += iDeltaX;
        this->nPosY += iDeltaY;
        this->lastupdate = currenttime;
        current_map.nOccupied[nPosY][nPosX] = 1;
        return true;
    }
    else
    {
        return false;
    }
}



bool AddNPCToList( friendly_npc *p_cfriendly_npc )
{
    for(int i = 0; i < 5; i++ )
    {
        if( p_cfriendly_npcList[i] == NULL )
        {
            p_cfriendly_npcList[i] = p_cfriendly_npc;
            //make NPC aware of his number
            p_cfriendly_npcList[i]->SetId(i);

            return true;
        }
    }


    return false;
}

bool RemoveActorFromList( friendly_npc *p_cfriendly_npc )
{
    for(int i = 0; i < 5; i++ )
    {
        if( p_cfriendly_npcList[i] == p_cfriendly_npc )
        {

            delete p_cfriendly_npc;


            p_cfriendly_npcList[i] = NULL;


            return true;
        }
    }

    return false;
}


int friendly_npc::getNPCLocationX()
{
    return this->oPosX;
}

int friendly_npc::getNPCLocationY()
{
    return this->oPosY;
}
