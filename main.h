#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <list>
#include "globals.h"


sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
int window_x = desktop.width;
int window_y = desktop.height;
int viewport_x = window_x * 0.8;
int viewport_y = window_y * 0.8;
int minimap_x = window_x * 0.2;
int minimap_y = window_y * 0.2;
int item_list_x = viewport_x + round(desktop.width/80);
int item_list_y = round(desktop.width/80);
int gametext_y = viewport_y + round((desktop.width/80)*2);
int gametext_x = round((desktop.width/80)*2);
int visible_x = viewport_x/32;
int visible_y = viewport_y/32;
sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Test Game", sf::Style::Fullscreen);
sf::RenderTexture minimapTexture;
bool minimapTextureExist = false;
sf::View view1(sf::FloatRect(0, 0, viewport_x,viewport_y));
sf::View minimap(sf::FloatRect(0, 0, minimap_x, minimap_y));
sf::View totalview = window.getDefaultView();
int enemies[2][99] = {10};






