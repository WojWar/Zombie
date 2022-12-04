#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>  
#include "Zombie.h"
#include "Map.h"

class Player: public sf::RectangleShape
{
public:
	Player(int points_of_health);
	Player();
	~Player();
public:
	sf::Vector2f velocity{ sf::Vector2f(0.0f, 0.0f) };
	sf::Vector2f pos;
	sf::Vector2i getSize();
	char jumpCounter{ 0 };
	void performMove(float frame_time);
	void are_close(const std::vector<Zombie*> &_Objects,float frame_time);
	bool intersectsSomething{ false };
	bool isAlive();
	void loseOneLivePoint();
	void jumpRequest();
public:
	bool shooting_direction{ true };
	int size_of_player_x{ 10 };
	float size_x{ 10 };
	int size_of_player_y{ 14 };  // change this value to bigger - game is frozen. why?
	int nr{ 0 };
	std::vector <int> numery;
	int pos_x, pos_y;
	bool ispixel{ false };
private:

	sf::Vector2f playerOffset{ sf::Vector2f(size_of_player_x / 2, size_of_player_y / 2) };
	void gravity_acceleration(float frame_time);

	Map groundMap{ sf::Vector2i(size_of_player_x, size_of_player_y) };
	short health;
	bool bites_me{ false };
	bool jump{ false };
	float gravitySpeed{ 0.f };
};

