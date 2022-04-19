#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>  
#include "Zombie.h"

class Player: public sf::RectangleShape
{
public:
	Player(int points_of_health);
	~Player();
public:
	sf::Vector2f velocity;
	sf::Vector2f pos;
	char jumpCounter = 0;
	void collision(const std::vector<RectangleShape> &_vectorObjects, char **_tab, int **_nr_of_object, float frame_time);
	void are_close(const std::vector<Zombie*> &_Objects,float frame_time);
	bool intersectsSomething;
	bool zombie_bites_player(const std::vector<Zombie*> &_Objects);
	void gravity_acceleration(float _gravity, float _jumpspeed);
public:
	char health;
	bool shooting_direction;
	int size_of_player_x;
	int size_of_player_y;
	int nr;
	std::vector <int> numery;
	int pos_x, pos_y;
	bool ispixel;
private:
	bool bites_me;
};

