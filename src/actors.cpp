#include "actors.h"
#include "gamemap.h"
#include "gameengine.h"
#include "player.h"
#include "soundsystem.h"


Cells cellsList[MAP_HEIGHT*MAP_WIDTH];

Actor *	p_cActorList[ MAX_ACTORS ];
bool AddActorToList( Actor *p_cNewActor );
bool RemoveActorFromList( Actor *p_cNewActor );

void Cells::updateCells()
{
    int n = 0;
    for(int i = 0; i < MAP_WIDTH; i++)
    {
        for(int j = 0; j < MAP_HEIGHT; j++)
        {
            cellsList[n].positionX = i;
            cellsList[n].positionY = j;
            if(n == (Player.position_x*MAP_HEIGHT)+Player.position_y)
            {
                cellsList[n].obstacle = false;
            }
            else if(!current_map.ispassable(i, j, false, false))
            {
                cellsList[n].obstacle = true;
            }
            else
            {
                cellsList[n].obstacle = false;
            }
            cellsList[n].costToGoal = NULL;
            cellsList[n].visited = false;
            cellsList[n].parentCellId = NULL;
            cellsList[n].cummulativeCost = NULL;
            cellsList[n].totalCostGuess = NULL;
            cellsList[n].neighbours.clear();
            cellsList[n].cellId = n;
            n++;
        }
    }

    for(int i = 0; i < (MAP_HEIGHT*MAP_WIDTH) ; i++)
    {
        if(cellsList[i].positionX > 0)
        {
            //de cell links kan toegevoegd worden
            if(!cellsList[i-MAP_HEIGHT].obstacle)
            {
                cellsList[i].neighbours.push_back(i-MAP_HEIGHT);
            }
        }
        if(cellsList[i].positionX < MAP_WIDTH-1)
        {
            //de cell rechts kan toegevoegd worden
            if(!cellsList[i+MAP_HEIGHT].obstacle)
            {
                cellsList[i].neighbours.push_back(i+MAP_HEIGHT);
            }
        }
        if(cellsList[i].positionY > 0)
        {
            //de cell erboven kan toegevogd worden
            if(!cellsList[i-1].obstacle)
            {
                cellsList[i].neighbours.push_back(i-1);
            }
        }
        if(cellsList[i].positionY != MAP_HEIGHT-1)
        {
            //de cell eronder kan toegevoegd worden
            if(!cellsList[i+1].obstacle)
            {
                cellsList[i].neighbours.push_back(i+1);
            }
        }
        //schuin gaan...
        if(cellsList[i].positionY != MAP_HEIGHT-1 && cellsList[i].positionX < MAP_WIDTH-1)
        {
            //de cell rechtsonder kan toegevoegd worden
            if(!cellsList[i+1+MAP_HEIGHT].obstacle )
            {
                if(cellsList[i+1].obstacle  && cellsList[i+MAP_HEIGHT].obstacle)
                {
                    //Dit hokje wordt door de twee buur hokjes geblokkeerd!
                }
                else
                {
                    cellsList[i].neighbours.push_back(i+1+MAP_HEIGHT);
                }
            }
        }
        if(cellsList[i].positionY >0 && cellsList[i].positionX < MAP_WIDTH-1)
        {
            //de cell rechtsboven kan toegevoegd worden
            if(!cellsList[i-1+MAP_HEIGHT].obstacle)
            {
                if(cellsList[i-1].obstacle && cellsList[i+MAP_HEIGHT].obstacle)
                {
                    //Dit hokje wordt door de twee buur hokjes geblokkeerd!
                }
                else
                {
                    cellsList[i].neighbours.push_back(i-1+MAP_HEIGHT);
                }
            }
        }
        if(cellsList[i].positionY != MAP_HEIGHT-1 && cellsList[i].positionX > 0)
        {
            //de cell linksonder kan toegevoegd worden
            if(!cellsList[i+1-MAP_HEIGHT].obstacle)
            {
                if(cellsList[i+1].obstacle && cellsList[i-MAP_HEIGHT].obstacle)
                {
                    //Dit hokje wordt door de twee buur hokjes geblokkeerd!
                }
                else
                {
                    cellsList[i].neighbours.push_back(i+1-MAP_HEIGHT);
                }
            }
        }
        if(cellsList[i].positionY >0 && cellsList[i].positionX > 0)
        {
            //de cell rechtsboven kan toegevoegd worden
            if(!cellsList[i-1-MAP_HEIGHT].obstacle)
            {
                if(cellsList[i-MAP_HEIGHT].obstacle && cellsList[i-1].obstacle)
                {
                    //Dit hokje wordt door de twee buur hokjes geblokkeerd!
                }
                else
                {
                    cellsList[i].neighbours.push_back(i-1-MAP_HEIGHT);
                }
            }
        }
    }
}






Actor::Actor( void )
{
    this->nPosX = 0;
    this->nPosY = 0;
    this->oPosX = 0;
    this->oPosY = 0;
    this->lastupdate= 0;
}

void Actor::SetAppearance()
{
// nog te maken. Speciale creeps/eindbaas enz
}

void Actor::SetPos( int x, int y, int health)
{
    if( (x < 0) || (x >= MAP_WIDTH) ||
            (y< 0) || (y >= MAP_HEIGHT ) )
        return;

    this->nPosX = x;
    this->nPosY = y;
    this->health = health;
}

void Actor::Draw( float currenttime )
{
    float plh = this->health;
    float hbx = (plh/100)*32;
    sf::RectangleShape health_bar_front;
    sf::RectangleShape health_bar_background;
    health_bar_background.setSize(sf::Vector2f( 32, 2 ));
    health_bar_front.setSize(sf::Vector2f(hbx, 2 ));
    health_bar_background.setOutlineThickness(1);
    health_bar_background.setOutlineColor(sf::Color::Black);
    health_bar_background.setFillColor(sf::Color::Red);
    health_bar_front.setFillColor(sf::Color::Green);
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
        Game.sActor.setPosition(tempx1, tempy1);
        health_bar_background.setPosition(tempx*32, tempy*32+34);
        health_bar_front.setPosition(tempx*32, tempy*32+34);
    }
    else
    {
        Game.sActor.setPosition(this->nPosX*32+16, this->nPosY*32+16);
        health_bar_background.setPosition(this->nPosX*32, this->nPosY*32+34);
        health_bar_front.setPosition(this->nPosX*32, this->nPosY*32+34);
    }
    if(this->attacking + 0.3 > currenttime)
    {
        window.setView(totalview);
        Game.Gametext("You are being attacked!!!");
        window.setView(view1);
    }
    window.draw(Game.sActor);
    window.draw(health_bar_background);
    window.draw(health_bar_front);
}


bool Actor::changePositionIfAvailable(int iDeltaX, int iDeltaY, float currenttime, bool absolute)
{
    if(absolute)
    {
        if( current_map.ispassable(iDeltaX, iDeltaY, false, false) )
        {
            current_map.nOccupied[nPosY][nPosX] = 0;
            this->oPosX = nPosX;
            this->oPosY = nPosY;
            this->nPosX = iDeltaX;
            this->nPosY = iDeltaY;
            this->lastupdate = currenttime;
            current_map.nOccupied[nPosY][nPosX] = 1;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
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
}

double dist(double x1, double y1, double x2, double y2)
{
    double x = x1 - x2; //calculating number to square in next step
    double y = y1 - y2;
    double dist;
    dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
    dist = sqrt(dist);
    return dist;
}

void Actor::Update( float currenttime )
{
    if(this->lastupdate + 0.3 < currenttime)
    {
        int iDeltaX;
        int iDeltaY;
        //check if the bot can attack the player:
        if((this->nPosX == Player.position_x || this->nPosX + 1 == Player.position_x || this->nPosX - 1 == Player.position_x) && (this->nPosY + 1 == Player.position_y ||this->nPosY - 1 == Player.position_y || this->nPosY == Player.position_y ))
        {
            //the bot attacks the player
            Player.health = Player.health - (2-(Player.armor/100));
            attacking = currenttime;
        }
        else
        {
            //callculate route to player
            cellsList->updateCells();
            std::list<Cells*> listToCheck;
            int startCell = (nPosX*MAP_HEIGHT)+nPosY;
            int endCell = (Player.position_x*MAP_HEIGHT)+Player.position_y;
            listToCheck.push_back(&cellsList[startCell]);
            cellsList[startCell].visited = true;
            this->pathFound = false;
            //check if player is nearby
            float distanceXToPlayer = Player.position_x - nPosX;
            float distanceYToPlayer = Player.position_y - nPosY;
            float pyDistance = sqrtf(distanceXToPlayer*distanceXToPlayer + distanceYToPlayer*distanceYToPlayer);
            if(pyDistance < 10)
            {
                while(!listToCheck.empty())
                {
                    //sorteer de lijst en zet de cell met de laagste cost to goal bovenaan om het eerst te testen
                    listToCheck.sort([](const Cells* f, const Cells* s)
                    {
                        return f->totalCostGuess < s->totalCostGuess;
                    });
                    //Check of de te checken cell het doel is. Als dat zo is zijn we klaar
                    if((*listToCheck.front()).cellId == endCell)
                    {
                        listToCheck.clear();
                        this->pathFound = true;
                    }
                    else
                    {
                        for (std::list<int>::const_iterator iterator =  (*listToCheck.front()).neighbours.begin(), end =  (*listToCheck.front()).neighbours.end(); iterator != end; ++iterator)
                        {
                            //We have found neighbours!
                            //check if neighbours was found before
                            if(!cellsList[*iterator].visited)
                            {
                                //Deze cell heeft geen parent is is dus nooit eerder gevonden!
                                //De cell waarvan we de neighbours onderzoeken is dus automagisch tot nu toe de kortste route hiernaartoe
                                cellsList[*iterator].parentCellId = (*listToCheck.front()).cellId;
                                //Nu moeten de kosten voor de route hiernatoe uitgerekend worden (Dit zijn de kosten van naar de buurman gaan +1
                                cellsList[*iterator].cummulativeCost = (*listToCheck.front()).cummulativeCost+1;
                                //Als laatste zetten we de cell in de lijst met cellen die gecheckt moet worden
                                listToCheck.push_back(&cellsList[*iterator]);
                                //Bereken de afstand naar het doel
                                cellsList[*iterator].costToGoal = dist(cellsList[*iterator].positionX,cellsList[*iterator].positionY,cellsList[endCell].positionX,cellsList[endCell].positionY);
                                cellsList[*iterator].totalCostGuess = cellsList[*iterator].costToGoal + cellsList[*iterator].cummulativeCost;
                                cellsList[*iterator].visited = true;
                            }
                            else
                            {
                                //Deze cell is al eerder gevonden, staat dus al in de te checken cell lijst
                                if((*listToCheck.front()).cummulativeCost+1 < cellsList[*iterator].cummulativeCost)
                                {
                                    //Er is een kortere route naar deze cell! Pas de parent cell dus aan en geef een nieuwe cummulative Cost;
                                    cellsList[*iterator].parentCellId = (*listToCheck.front()).cellId;
                                    cellsList[*iterator].cummulativeCost = (*listToCheck.front()).cummulativeCost+1;
                                    cellsList[*iterator].totalCostGuess = cellsList[*iterator].costToGoal + cellsList[*iterator].cummulativeCost;
                                }
                            }
                        }
                        listToCheck.pop_front();
                    }
                }
            }
            //Zet de te lopen route in een lijst
            this->route.clear();
            this->route.push_back(cellsList[endCell]);
            if(this->pathFound)
            {
                bool endReached = false;
                while(!endReached)
                {
                    this->route.push_back(cellsList[route.back().parentCellId]);
                    if(this->route.back().parentCellId == startCell)
                    {
                        endReached = true;
                    }
                }
            }
            if(!this->route.empty() )
            {
                if(route.back().cellId == (Player.position_x*MAP_HEIGHT)+Player.position_y)
                {
                    this->route.pop_back();
                }
            }
            if(!this->route.empty() )
            {
                iDeltaX = this->route.back().positionX;
                iDeltaY = this->route.back().positionY;
                if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, true)) { }
                this->route.pop_back();
            }
            else
            {
                if(pyDistance < 3)
                {
                    if(distanceXToPlayer > 0)
                    {
                        iDeltaX = 1;
                    }
                    else if(distanceXToPlayer < 0)
                    {
                        iDeltaX = -1;
                    }
                    else
                    {
                        iDeltaX = 0;
                    }
                    if(distanceYToPlayer > 0)
                    {
                        iDeltaY = 1;
                    }
                    else if(distanceYToPlayer < 0)
                    {
                        iDeltaY = -1;
                    }
                    else
                    {
                        iDeltaY = 0;
                    }
                    // See if this new position is allowed
                    if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                    {
                        int iDeltaXOriginal = iDeltaX;
                        int iDeltaYOriginal = iDeltaY;
                        if(distanceXToPlayer > distanceYToPlayer)
                        {
                            iDeltaY = 0;
                            if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                            {
                                iDeltaY = -1;
                                if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                {
                                    iDeltaY = 1;
                                    if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                    {
                                        iDeltaY = iDeltaYOriginal;
                                        iDeltaX = 0;
                                        if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                        {
                                            iDeltaX = 1;
                                            if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                            {
                                                iDeltaX = -1;
                                                if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                                {
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            iDeltaX = 0;
                            if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                            {
                                iDeltaX = -1;
                                if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                {
                                    iDeltaX = 1;
                                    if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                    {
                                        iDeltaX = iDeltaXOriginal;
                                        iDeltaY = 0;
                                        if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                        {
                                            iDeltaY = 1;
                                            if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                            {
                                                iDeltaY = -1;
                                                if(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false))
                                                {
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    iDeltaX = (rand() % 3) - 1;
                    iDeltaY = (rand() % 3) - 1;
                    int tries = 0;
                    while(!changePositionIfAvailable(iDeltaX, iDeltaY, currenttime, false) && tries < 8)
                    {
                        iDeltaX = (rand() % 3) - 1;
                        iDeltaY = (rand() % 3) - 1;
                        tries++;
                    }
                }
            }

        }
        if(attacking == currenttime)
        {
            Audio.sbuffer1.loadFromFile("audio/enemy fire.wav");
            Audio.sound1.setBuffer(Audio.sbuffer1);
            Audio.sound1.play();
        }
    }
}

bool Actor::TakeDamage(int x, int y, int amount)
{
    if(this->nPosX == x && this->nPosY == y)
    {
        this->health = this->health - amount;
        if(this->health <= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


int Actor::getActorLocationX()
{
    return this->oPosX;
}

int Actor::getActorLocationY()
{
    return this->oPosY;
}

bool AddActorToList( Actor *p_cNewActor )
{
    for(int i = 0; i < MAX_ACTORS; i++ )
    {
        if( p_cActorList[i] == NULL )
        {
            p_cActorList[i] = p_cNewActor;

            return true;
        }
    }


    return false;
}

bool RemoveActorFromList( Actor *p_cActor )
{
    for(int i = 0; i < MAX_ACTORS; i++ )
    {
        if( p_cActorList[i] == p_cActor )
        {

            delete p_cActor;


            p_cActorList[i] = NULL;


            return true;
        }
    }

    return false;
}
