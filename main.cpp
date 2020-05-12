#include "main.h"
#include "actors.h"
#include "gamemap.h"
#include "gameengine.h"
#include "player.h"
#include "soundsystem.h"
#include "npc.h"

/************************************************************************************************
*                                                                                               *
*                      Section:  Game Engine                                                    *
*                                                                                               *
************************************************************************************************/


/************************************************************************************************
*                                                                                               *
*                      Section:  Game Map                                                       *
*                                                                                               *
************************************************************************************************/

/************************************************************************************************
*                                                                                               *
*                      Section:  Player                                                         *
*                                                                                               *
************************************************************************************************/


/************************************************************************************************
*                                                                                               *
*                      Section:  Sound System                                                   *
*                                                                                               *
************************************************************************************************/



/************************************************************************************************
*                                                                                               *
*                      Section:  NPC                                                            *
*                                                                                               *
************************************************************************************************/


/************************************************************************************************
*                                                                                               *
*                      Section:  Item Shop                                                      *
*                                                                                               *
************************************************************************************************/


/************************************************************************************************
*                                                                                               *
*                      Section:  Cells                                                          *
*                                                                                               *
************************************************************************************************/

/************************************************************************************************
*                                                                                               *
*                      Section:  Main game loop                                                 *
*                                                                                               *
************************************************************************************************/


int main()
{
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);
    view1.setViewport(sf::FloatRect(0, 0, 0.8f, 0.8f));
    minimap.setViewport(sf::FloatRect(0.8f,0.8f,0.2f,0.2f));
    Game.menu();
    Game.Gametext("Game is loading, please wait...");
    window.display();
    sf::Clock clock;
    sf::Clock clockMain;
    float timepressed = -1;
    float timepressedA = -1;
    float timepressedQ = -1;
    float timepressedE = -1;
    float timepressed_up = -1;
    float timepressed_down = -1;
    float timepressed_left = -1;
    float timepressed_right = -1;
    float timepressed_x = -1;
    float timepressed_y = -1;
    float BoatPressed = -1;
    float NothingHereText = -1;
    float water = 0;
    int watertile = 0;
    int hastalked = 0;
    bool focus = true;
    bool inBoat = false;
    Game.loadtextures();
    Game.Initialize();
    int change_x = 0, change_y = 0;
    Audio.play_music(0);
    while (window.isOpen())
    {
        Game.gametext = 0;
        window.clear();
        bool f = false;
        sf::Time elapsed1 = clock.getElapsedTime();
        if(Player.health <= 0)
        {
            Player.died();
        }
        if(current_map.nMapArray[Player.position_y][Player.position_x] == 7)
        {
            Game.load_next_level();
        }
        if(current_map.nMapArray[Player.position_y][Player.position_x] == 8)
        {
            Game.load_prev_level();
        }
        if(current_map.nMapArray[Player.position_y][Player.position_x] == 9)
        {
            Game.switch_dungeon();
        }
        sf::Time elapsedMain = clockMain.getElapsedTime();
        if((timepressed_x + 0.3) < elapsedMain.asSeconds())
        {
            change_x = 0;
        }
        if((timepressed_y + 0.3) < elapsedMain.asSeconds())
        {
            change_y = 0;
        }
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
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                Audio.play_music(-2);
                Game.menu();
                Audio.play_music(-1);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (timepressed_y + 0.3) < elapsedMain.asSeconds())
            {
                Player.porientation = 1;
                timepressed = elapsedMain.asSeconds();
                timepressed_y = elapsedMain.asSeconds();
                timepressed_up = elapsedMain.asSeconds();
                if(current_map.ispassable(Player.position_x, Player.position_y - 1, false, inBoat))
                {
                    current_map.nOccupied[Player.position_y][Player.position_x] = 0;
                    Player.position_y = Player.position_y - 1;
                    change_y = -1;
                    current_map.nOccupied[Player.position_y][Player.position_x] = 1;
                }
                else
                {
                    Audio.sbuffer1.loadFromFile("audio/Lock.wav");
                    Audio.sound1.setBuffer(Audio.sbuffer1);
                    Audio.sound1.play();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (timepressed_y + 0.3) < elapsedMain.asSeconds())
            {
                Player.porientation = 2;
                timepressed = elapsedMain.asSeconds();
                timepressed_y = elapsedMain.asSeconds();
                timepressed_down = elapsedMain.asSeconds();
                if(current_map.ispassable(Player.position_x, Player.position_y + 1, false, inBoat) == true)
                {
                    current_map.nOccupied[Player.position_y][Player.position_x] = 0;
                    Player.position_y = Player.position_y + 1;
                    change_y = 1;
                    current_map.nOccupied[Player.position_y][Player.position_x] = 1;
                }
                else
                {
                    Audio.sbuffer1.loadFromFile("audio/Lock.wav");
                    Audio.sound1.setBuffer(Audio.sbuffer1);
                    Audio.sound1.play();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (timepressed_x + 0.3) < elapsedMain.asSeconds())
            {
                Player.porientation = 3;
                timepressed = elapsedMain.asSeconds();
                timepressed_x = elapsedMain.asSeconds();
                timepressed_right = elapsedMain.asSeconds();
                if(current_map.ispassable(Player.position_x+1, Player.position_y, false, inBoat))
                {
                    current_map.nOccupied[Player.position_y][Player.position_x] = 0;
                    Player.position_x = Player.position_x + 1;
                    change_x = 1;
                    current_map.nOccupied[Player.position_y][Player.position_x] = 1;
                }
                else
                {
                    Audio.sbuffer1.loadFromFile("audio/Lock.wav");
                    Audio.sound1.setBuffer(Audio.sbuffer1);
                    Audio.sound1.play();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (timepressed_x + 0.3) < elapsedMain.asSeconds())
            {
                Player.porientation = 4;
                timepressed = elapsedMain.asSeconds();
                timepressed_x = elapsedMain.asSeconds();
                timepressed_left = elapsedMain.asSeconds();
                if(current_map.ispassable(Player.position_x-1, Player.position_y, false, inBoat))
                {
                    current_map.nOccupied[Player.position_y][Player.position_x] = 0;
                    Player.position_x = Player.position_x - 1;
                    change_x = -1;
                    current_map.nOccupied[Player.position_y][Player.position_x] = 1;
                }
                else
                {
                    Audio.sbuffer1.loadFromFile("audio/Lock.wav");
                    Audio.sound1.setBuffer(Audio.sbuffer1);
                    Audio.sound1.play();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)&& (timepressedE + 0.3) < elapsedMain.asSeconds())
            {
                timepressedE = elapsedMain.asSeconds();
                int i = Player.Pick_Up_Item();
                if(i == 1)
                {
                    BoatPressed = elapsedMain.asSeconds();
                }
                if(i == 2)
                {
                    NothingHereText = elapsedMain.asSeconds();
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                Player.DropItem();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                Player.UseItem();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                Player.UseDoor();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                Player.Talk(elapsedMain.asSeconds());
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (timepressedA + 0.3) < elapsedMain.asSeconds())
            {
                timepressedA = elapsedMain.asSeconds();
                Player.Do_Attack();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && (timepressedQ + 0.3) < elapsedMain.asSeconds() && Player.mana >= 10)
            {
                timepressedQ = elapsedMain.asSeconds();
                Player.Do_Magic_Attack();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                Player.Shoot_Arrow(elapsedMain.asSeconds()+0.30);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            {
                inBoat = Player.boardShip(inBoat);
            }
        }
        if(elapsed1.asSeconds() >= 0.3)
        {
            if(Player.mana < Player.max_mana)
            {
                Player.mana = Player.mana + 0.25;
            }
            f = true;
            clock.restart();
        }
        for(int i = 0; i < MAX_ACTORS; i++ )
        {
            if(p_cActorList[i] != NULL )
            {
                if(f)
                {
                    p_cActorList[i]->Update(elapsedMain.asSeconds());
                }
            }
        }

        Player.Level_up();
        float currentTime = elapsedMain.asSeconds();
        Player.OrientPlayer(timepressed_x, timepressed_y, timepressed_up, timepressed_down, timepressed_left, timepressed_right, currentTime);
        Game.move_view(change_x, change_y, currentTime, timepressed, timepressed_x, timepressed_y);
        if(currentTime > water + 0.3)
        {
            water = currentTime;
            watertile = Game.Watertexture(watertile);
        }
        window.setView(totalview);
        window.draw(Game.sGameBackground);
        window.setView(view1);
        current_map.DrawMap();
        current_map.DrawItems();
        for(int i = 0; i < MAX_ACTORS; i++ )
        {
            if(p_cActorList[i] != NULL )
            {
                p_cActorList[i]->Draw(elapsedMain.asSeconds());
            }
        }
        for(int i = 0; i < 5; i++ )
        {
            if(p_cfriendly_npcList[i] != NULL )
            {
                p_cfriendly_npcList[i]->update_npc(currentTime);
                p_cfriendly_npcList[i]->draw(currentTime);
            }
        }
        Player.DrawPlayer(change_x, change_y, timepressed, elapsedMain.asSeconds());
        current_map.drawMiniMap();
        window.setView(totalview);
        if (BoatPressed + 1 > elapsedMain.asSeconds())
        {
            Game.Gametext("You want to carry a boat?!");
        }
        if (NothingHereText + 1 > elapsedMain.asSeconds())
        {
            Game.Gametext("Nothing to pick up!");
        }
        if(Player.health <= 25)
        {
            Game.Gametext("Hint: You are low on health, use a potion!");
        }

        Game.DrawItemList(0);
        window.display();
    }
    return 0;
}
