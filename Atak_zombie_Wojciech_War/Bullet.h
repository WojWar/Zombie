#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>  
#include "Player.h"
class Bullet : public sf::RectangleShape
{
public:
	Bullet(const Player &_player);
	~Bullet();
	sf::Vector2f velocity;

	//methods
	bool is_wall(char **_tab);

	void setPosition(sf::Vector2f pos);

};

