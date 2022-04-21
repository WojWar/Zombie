#pragma once

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "Globals.h"

using namespace sf;

class BgWalls
{
public:
	BgWalls();
	~BgWalls();

	void Init(sf::Image &_mapImage);

	char **getBgWallsTab();

private:

	//tablice dla scian ograniczajacych:
	char **tab_RED; // tutaj wartosc 0 lub 1 czy jest sciana

};

