#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>  
#include "Zombie.h"
#include "GameMap.h"

class Player: public sf::RectangleShape
{
public:
	Player(int points_of_health, GameMap &gameMap);
	Player();
	~Player();
public:
	sf::Vector2f velocity{ sf::Vector2f(0.0f, 0.0f) };
	sf::Vector2f pos;
	sf::Vector2i getSize();
	char jumpCounter{ 0 };
	void performMove(float frame_time);
	void areClose(const std::vector<Zombie*> &_Objects,float frame_time);
	bool intersectsSomething{ false };
	bool isAlive();
	void loseOneLivePoint();
	void jumpRequest();
public:
	bool shooting_direction{ true };
	int size_of_player_x{ 10 };
	int size_of_player_y{ 14 };  // change this value to bigger - game is frozen. why?

	int nr{ 0 };
	std::vector <int> numery;
	sf::Vector2f playerSize{ sf::Vector2f(10.0f, 14.0f) };
	sf::Vector2f startPosition{ sf::Vector2f(50.0f, 400.0f) };
private:
	GameMap* groundMap;
	//GameMap groundMap{ sf::Vector2i(size_of_player_x, size_of_player_y) };
	sf::Vector2f playerOffset{ sf::Vector2f(5.0f, 7.0f) };
	void gravityAcceleration(float frame_time);

	short health;
	bool zombieBitesMe{ false };
	bool jump{ false };
	float gravitySpeed{ 0.f };
};

