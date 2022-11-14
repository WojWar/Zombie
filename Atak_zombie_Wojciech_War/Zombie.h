#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include "Globals.h"
#include "BgWalls.h"

 
class Zombie: public sf::RectangleShape
{
public:
	Zombie(int points_of_health, sf::Vector2f _pos);
	~Zombie();
public:
	void randVelocity();
	void randsmallVelocity();
	void collision(const std::vector<RectangleShape> &_vectorObjects, char **_tab, int **_nr_of_object,float fps_time);

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
	sf::Vector2i size_of_zombie = sf::Vector2i(5, 10);
	sf::Vector2f fsize_of_zombie = sf::Vector2f(5.0f, 10.0f);


};

 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////