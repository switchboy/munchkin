#include "soundsystem.h"
#include <iostream>

Sound_System Audio;

void Sound_System::play_music(int i)
{

    switch ((int) i)
    {
    //check of de muziek gepauzeerd of hervat moet worden.
    case -2:
        music.pause();
        break;

    case -1:
        music.play();
        break;

    //Er moet moet (andere) muziek gespeeld worden
    case 0:
        if(this->music_playing)
        {
            music.stop();
        }
        if (!music.openFromFile("audio/gamemusic.wav"))
        {
            std::cout << "Error loading music!" << std::endl;
        }
        music.setLoop(true);
        music.play();
        break;

    case 1:
        if(this->music_playing)
        {
            music.stop();
        }
        if (!music.openFromFile("audio/dungeon_music.wav"))
        {
            std::cout << "Error loading music!" << std::endl;
        }
        music.setLoop(true);
        music.play();
        break;


    default:
        if(this->music_playing)
        {
            music.stop();
        }
        if (!music.openFromFile("audio/gamemusic.wav"))
        {
            std::cout << "Error loading music!" << std::endl;
        }
        music.setLoop(true);
        music.play();
        break;
    }
}
