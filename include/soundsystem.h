#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H
#include <SFML/Audio.hpp>

class Sound_System
{
public:
    sf::Music music;
    sf::Sound sound;
    sf::Sound sound1;
    sf::Sound sound2;
    sf::Sound sound3;
    sf::Sound sound4;
    sf::Sound sound5;
    sf::Sound sound6;
    sf::SoundBuffer sbuffer6;
    sf::SoundBuffer sbuffer5;
    sf::SoundBuffer sbuffer4;
    sf::SoundBuffer sbuffer;
    sf::SoundBuffer sbuffer1;
    sf::SoundBuffer sbuffer2;
    sf::SoundBuffer sbuffer3;
    void play_music(int i);
protected:
    bool music_playing = false;

};

extern Sound_System Audio;

#endif // SOUNDSYSTEM_H
