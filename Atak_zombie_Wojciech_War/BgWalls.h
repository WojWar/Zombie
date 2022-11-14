#pragma once

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Globals.h"

using namespace sf;

class BgWalls
{
public:
	BgWalls();
	~BgWalls();

	void Init(sf::Image &_mapImage);
	bool isWall(int x, int y);

private:

	int walls_count{ 0 };
	int wallsMapWidth;
	int wallsMapHeight;

	// 2D mapa scian ograniczajacych:
	// wartosc 0 lub 1 czy jest sciana
	std::vector<std::vector<bool>> map2d;
};

