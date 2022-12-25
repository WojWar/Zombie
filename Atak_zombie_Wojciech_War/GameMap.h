#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Matrix2d.h"

class GameMap
{
public:
	GameMap(sf::Vector2i playerSize);
	~GameMap();
public:
	bool isGround(int x, int y);
	bool isGround(sf::Vector2f coordinates);
	bool isGround(float x, float y);
	void loadGround();
private:
	//returns a black pixel directly from image
	bool imageGetPoint(unsigned int point_x, unsigned int point_y);

	void setUp(unsigned int point_x, unsigned int point_y);
	void setDown(unsigned int point_x, unsigned int point_y);
	void setLeft(unsigned int point_x, unsigned int point_y);
	void setRight(unsigned int point_x, unsigned int point_y);

	void setRightUp(unsigned int point_x, unsigned int point_y);
	void setLeftUp(unsigned int point_x, unsigned int point_y);
	void setRightDown(unsigned int point_x, unsigned int point_y);
	void setLeftDown(unsigned int point_x, unsigned int point_y);

private:
	int mapWidth;
	int mapHeight;
	sf::Vector2i playerOffset;
	sf::Image _mapImage;
	std::string mapName;

	Matrix2d hardGround;

};

