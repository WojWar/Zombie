#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>  
#include "Player.h"
class Bullet : public sf::RectangleShape
{
public:
	Bullet(Player &_player);
	~Bullet();
	sf::Vector2f velocity;

	bool is_wall(char _tab[][576]);
	bool is_zombie(std::vector<Zombie*> &_vectorZombies);
	bool is_shooted_value;
};

