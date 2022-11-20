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


class Game
{
public:
	//
	Game();
	~Game();

	void play();

private:
	//podloze i sciany ograniczajace:
	std::vector <sf::RectangleShape> groundRectangles;

	//std::forward_list <Bullet*> vectorBullets;
	Bullets bullets;

	//pasek zycia:
	std::vector <sf::RectangleShape*> vectorHealth;

	//mapa:
	sf::Image _mapImage;

	//tablice dla podloza:
	char **tab; // tutaj wartosc 0 lub 1 czy jest grunt
	int **nr_of_object; // tutaj nr obiektu w vectorze ktory jest w danym pixelu


	//methods 

	void objects_to_vector_and_texture(sf::RenderTexture &_textura, std::string &_map_name);
	void initialize_health_bar(sf::RenderWindow &_okno, sf::RenderTexture &_textura, const Player &_player);

	sf::RenderWindow *okno;
};

