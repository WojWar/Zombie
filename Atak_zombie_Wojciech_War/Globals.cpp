
#include "Globals.h"

// globals 

const float gravity = 0.001f;
int zombie_health = 50; //5;
int player_health = 150; // 15;
float movespeedPlayer = 0.1f, jumpspeed = 0.4f;
float movespeedZombie = 0.1f;
int windowHeight = 576;
int windowWidth = 1024;

std::string map_names[3] = { "map_01.png", "map_02.png", "map_03.png" };
std::string map_name = map_names[0];