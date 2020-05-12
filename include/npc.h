#ifndef NPC_H
#define NPC_H
#include <string>

class friendly_npc
{
public:
    friendly_npc(void);
    void    SetPos( int x, int y);
    void    SetType(int type);
    void    SetId(int id);
    void    update_npc(float currenttime);
    std::string    interact_npc(int pos_x, int pos_y, float currenttime);
    int     getValue( int value);
    void    draw(float currenttime);
    int     getNPCLocationX();
    int     getNPCLocationY();
private:
    // Horizontal coordinate of the actor, relative to the level's origin
    int     nPosX;
    int     oPosX;
    // Vertical coordinate of the actor, relative to the level's origin.
    int     nPosY;
    int     oPosY;
    int     npc_kind;
    int     npcId;
    float   lastupdate;
    bool    changePositionIfAvailable(int iDeltaX, int iDeltaY, float currenttime);
    bool    awareOfPlayer;
};

extern friendly_npc *	p_cfriendly_npcList [ 5 ];
extern bool AddNPCToList( friendly_npc *p_cfriendly_npc );
extern bool RemoveActorFromList( friendly_npc *p_cfriendly_npc );


#endif // NPC_H
