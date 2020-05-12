#ifndef ACTORS_H
#define ACTORS_H
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "globals.h"

class Cells
{
public:
    int positionX, positionY, parentCellId, cummulativeCost, cellId;
    double costToGoal, totalCostGuess;
    bool visited = false;
    bool obstacle = false;
    std::list<int> neighbours;
    void updateCells();
};

extern Cells cellsList[MAP_HEIGHT*MAP_WIDTH];



class Actor
{

public:
    Actor( void );
    void	SetAppearance(  );
    void	SetPos( int x, int y, int health );
    void	Draw( float currenttime );
    void	Update( float currenttime );
    bool   TakeDamage(int x, int y, int amount);
    int getActorLocationX();
    int getActorLocationY();

protected:
    float   lastupdate;
    int     health;
    float   attacking = -0.3;
    int     nPosX;
    int     oPosX;
    int     nPosY;
    int     oPosY;
    bool    changePositionIfAvailable(int iDeltaX, int iDeltaY, float currenttime, bool absolute);
    std::list<Cells> route;
    bool    pathFound;


};

extern Actor *	p_cActorList[ MAX_ACTORS ];
extern bool AddActorToList( Actor *p_cNewActor );
extern bool RemoveActorFromList( Actor *p_cNewActor );

#endif // ACTORS_H
