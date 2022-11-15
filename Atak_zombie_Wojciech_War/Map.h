#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"

class Map
{
public:
	Map();
	~Map();
public:
	bool isGround(int x, int y);
	void initialise(sf::RenderTexture &_textura, std::string &_map_name);
private:

	std::vector<std::vector<bool>> map2d;
	int mapWidth;
	int mapHeight;

	//mapa:
	sf::Image _mapImage;

	//tablice dla podloza:
	char **tab; // tutaj wartosc 0 lub 1 czy jest grunt
	int **nr_of_object; // tutaj nr obiektu w vectorze ktory jest w danym pixelu

	//podloze i sciany ograniczajace:
	std::vector <sf::RectangleShape> groundRectangles;

};

