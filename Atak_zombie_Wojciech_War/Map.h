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
	void initialise(sf::RenderTexture &_textura);
	void loadGroundObjects();
	void loadGround();
private:

	int mapWidth;
	int mapHeight;
	std::string mapName;

	//mapa:
	sf::Image _mapImage;

	//tablice dla podloza:
	char **tab; // tutaj wartosc 0 lub 1 czy jest grunt
	int **nr_of_object; // tutaj nr obiektu w vectorze ktory jest w danym pixelu

	//podloze i sciany ograniczajace:
	std::vector <sf::RectangleShape> groundRectangles;
	std::vector<std::vector<bool>> map2d;
	//std::vector<std::vector<bool>> map2d;

};

