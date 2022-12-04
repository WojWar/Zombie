
#include "Globals.h"

// globals 

const float gravity = 0.001f;
int zombie_health = 2;
int player_health = 15;
float movespeedPlayer = 0.1f, jumpspeed = 0.4f;
float movespeedZombie = 0.1f;
const int windowHeight = 576;
const int windowWidth = 1024;

std::string map_names[3] = { "map_01.png", "map_02.png", "map_03.png" };
std::string map_name = map_names[0];