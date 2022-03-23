#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>  /*
#include "Bullet.h"*/

 
class Zombie: public sf::RectangleShape
{
public:
	Zombie(int points_of_health);
	~Zombie();
public:
	void randVelocity();
	void randsmallVelocity();
	void collision(std::vector<RectangleShape> &_vectorObjects, char _tab[][576], int _nr_of_object[][576],float fps_time);

	void collision_wall(char _tab[][576]); 

	void race_to_left(float frame_time);
	void race_to_right(float frame_time);

public:
	char health;
	sf::Vector2f velocity;
	sf::Vector2f position;
	bool intersectsSomething;
	int size_of_player_x;
	int size_of_player_y;
	int nr;
	std::vector <int> numery;
	int pos_x, pos_y;
	bool ispixel;
	bool bite;
private:
	const float movespeed = 0.1f;


};

 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////