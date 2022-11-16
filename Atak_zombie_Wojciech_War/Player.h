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
	Player();
	~Player();
public:
	sf::Vector2f velocity;
	sf::Vector2f pos;
	char jumpCounter{ 0 };
	void collision(const std::vector<RectangleShape> &_vectorObjects, char **_tab, int **_nr_of_object, float frame_time);
	void are_close(const std::vector<Zombie*> &_Objects,float frame_time);
	bool intersectsSomething{ false };
	bool isAlive();
	void loseOneLivePoint();
	void gravity_acceleration(float _gravity, float _jumpspeed);
public:
	bool shooting_direction{ true };
	int size_of_player_x{ 10 };
	int size_of_player_y{ 15 };
	int nr{ 0 };
	std::vector <int> numery;
	int pos_x, pos_y;
	bool ispixel{ false };
private:
	short health;
	bool bites_me{ false };
};

