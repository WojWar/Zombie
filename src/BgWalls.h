#pragma once

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Globals.h"

class BgWalls
{
public:
	BgWalls();
	~BgWalls();

	void Init(sf::Image &_mapImage);
	bool isWall(int x, int y);

private:

	int wallsCount{ 0 };
	int wallsMapWidth;
	int wallsMapHeight;

	std::vector<std::vector<bool>> map2d;
};

