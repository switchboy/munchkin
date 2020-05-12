#ifndef GLOBALS_H
#define GLOBALS_H
#include <SFML/Graphics.hpp>
#define MAP_WIDTH			200
#define MAP_HEIGHT			200
#define MAX_ACTORS			200


extern sf::VideoMode desktop;
extern int window_x;
extern int window_y;
extern int viewport_x;
extern int viewport_y;
extern int minimap_x;
extern int minimap_y;
extern int item_list_x;
extern int item_list_y;
extern int gametext_y;
extern int gametext_x;
extern int visible_x;
extern int visible_y;
extern sf::RenderWindow window;
extern sf::RenderTexture minimapTexture;
extern bool minimapTextureExist;
extern sf::View view1;
extern sf::View minimap;
extern sf::View totalview;
extern int enemies[2][99];

#endif // GLOBALS_H
