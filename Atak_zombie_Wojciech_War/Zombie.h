#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include "Globals.h"
#include "BgWalls.h"
#include "GameMap.h"

 
class Zombie: public sf::RectangleShape
{
public:
	Zombie(sf::Vector2f _pos, GameMap &gameMap);
	~Zombie();
public:
	void randVelocity();
	void randsmallVelocity();
	void collision(float fps_time);
	void collision_wall(BgWalls &_walls);
	void race_to_left(float frame_time);
	void race_to_right(float frame_time);

public:
	char health;
	sf::Vector2f velocity;
	sf::Vector2f position;
	int nr;
	std::vector <int> numery;
	int pos_x, pos_y;
	bool ispixel;
	bool bite;
private:
	void gravityAcceleration(float frame_time);
	sf::Vector2i size_of_zombie = sf::Vector2i(6, 10);
	sf::Vector2f fsize_of_zombie = sf::Vector2f(6.0f, 10.0f);
	sf::Vector2f zombieOffset{ sf::Vector2f(3.0f, 5.0f) };
	GameMap* zombieGroundMap;

};