#pragma once

//includes
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <cmath>  
#include "Zombies.h"
#include "Player.h"
#include "Bullets.h"
#include "Globals.h"
#include <ctime> 
#include <time.h>
#include <fstream> 
#include <stdio.h>
#include <sstream>
#include "GameMap.h"


class Game
{
public:
	//
	Game();
	~Game();

	void play();

private:


	//pasek zycia:
	std::vector <sf::RectangleShape*> vectorHealth;

	//mapa:
	sf::Image _mapImage;

	//tablice dla podloza:
	char **tab; // tutaj wartosc 0 lub 1 czy jest grunt


	//methods 

	void objects_to_vector_and_texture(sf::RenderTexture &_textura, std::string &_map_name);
	void initialize_health_bar(sf::RenderWindow &_okno, sf::RenderTexture &_textura, const Player &_player);

	sf::RenderWindow *okno;



	int Game_size_of_player_x{ 10 };
	int Game_size_of_player_y{ 14 };
	GameMap groundMap2{ sf::Vector2i(Game_size_of_player_x, Game_size_of_player_y) };
	Bullets bullets{ groundMap2 };
};

