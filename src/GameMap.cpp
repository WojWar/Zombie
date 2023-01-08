
#include <iostream>
#include "GameMap.h"
#include "Player.h"

GameMap::GameMap(sf::Vector2i playerSize):
	mapName(map_name),
	mapWidth(windowWidth),
	playerOffset(sf::Vector2i(playerSize.x/2, playerSize.y/2)),
	mapHeight(windowHeight)
{
	_mapImage.loadFromFile(mapName);
}

GameMap::~GameMap()
{
}

bool GameMap::isGround(int x, int y)
{
	//std::cout << "x: " << x << ", y: " << y << std::endl;
	if (x <= 0 or y <= 0) return true;
	return hardGround.getPoint((size_t)x, (size_t)y);
}

bool GameMap::isGround(float x, float y)
{
	//std::cout << "x: " << x << ", y: " << y << std::endl;
	if (x <= 0.0f or y <= 0.0f) return true;
	return hardGround.getPoint((unsigned int)x, (unsigned int)y);
}

bool GameMap::isGround(sf::Vector2f coordinates)
{
	//std::cout << "x: " << x << ", y: " << y << std::endl;
	if (coordinates.x <= 0.0f or coordinates.y <= 0.0f) return true;
	return hardGround.getPoint(coordinates);
}

void GameMap::loadGround()
{
	std::cout << std::endl << "Loading the ground map" << std::endl;
	int hOffset = playerOffset.x;
	int vOffset = playerOffset.y;

	sf::Vector2u imageSize = _mapImage.getSize();

	for (unsigned int y = 0; y < (unsigned int)windowHeight - 1; y++) {
		for (unsigned int x = 0; x < (unsigned int)windowWidth - 1; x++) {
			if (imageGetPoint(x, y))
			{
				hardGround.setPoint(x, y);

				if (!imageGetPoint(x+1, y))
				{
					setRight(x, y);
					if (!imageGetPoint(x, y + 1))
					{
						setRightUp(x, y);
					}
					if (!imageGetPoint(x, y - 1))
					{
						setRightDown(x, y);
					}
				}
				if (!imageGetPoint(x-1, y))
				{
					setLeft(x, y);
					if (!imageGetPoint(x, y + 1))
					{
						setLeftUp(x, y);
					}
					if (!imageGetPoint(x, y - 1))
					{
						setLeftDown(x, y);
					}
				}
				if (!imageGetPoint(x, y+1))
				{
					setUp(x, y);
				}
				if (!imageGetPoint(x, y-1))
				{
					setDown(x, y);
				}
			}
		}
	}

	std::cout << "Ground map loading finished." << std::endl;
}

bool GameMap::imageGetPoint(unsigned int point_x, unsigned int point_y)
{
	if (point_x > _mapImage.getSize().x
		or point_y > _mapImage.getSize().y)
	{
		return true;
	}
	if ((sf::Color::Black) == _mapImage.getPixel(point_x, point_y)) 
	{
		return true;
	}
	return false;
}

void GameMap::setUp(unsigned int point_x, unsigned int point_y)
{
	hardGround.setPoint(point_x, point_y + 1);
	hardGround.setPoint(point_x, point_y + 2);
	hardGround.setPoint(point_x, point_y + 3);
	hardGround.setPoint(point_x, point_y + 4);
	hardGround.setPoint(point_x, point_y + 5);
	hardGround.setPoint(point_x, point_y + 6);
}

void GameMap::setDown(unsigned int point_x, unsigned int point_y)
{
	hardGround.setPoint(point_x, point_y - 1);
	hardGround.setPoint(point_x, point_y - 2);
	hardGround.setPoint(point_x, point_y - 3);
	hardGround.setPoint(point_x, point_y - 4);
	hardGround.setPoint(point_x, point_y - 5);
	hardGround.setPoint(point_x, point_y - 6);
}

void GameMap::setRight(unsigned int point_x, unsigned int point_y)
{
	hardGround.setPoint(point_x + 1, point_y);
	hardGround.setPoint(point_x + 2, point_y);
	hardGround.setPoint(point_x + 3, point_y);
	hardGround.setPoint(point_x + 4, point_y);
}

void GameMap::setLeft(unsigned int point_x, unsigned int point_y)
{
	hardGround.setPoint(point_x - 1, point_y);
	hardGround.setPoint(point_x - 2, point_y);
	hardGround.setPoint(point_x - 3, point_y);
	hardGround.setPoint(point_x - 4, point_y);
}

void GameMap::setRightUp(unsigned int point_x, unsigned int point_y)
{
	setUp(point_x + 1, point_y);
	setUp(point_x + 2, point_y);
	setUp(point_x + 3, point_y);
	setUp(point_x + 4, point_y);
}

void GameMap::setLeftUp(unsigned int point_x, unsigned int point_y)
{
	setUp(point_x - 1, point_y);
	setUp(point_x - 2, point_y);
	setUp(point_x - 3, point_y);
	setUp(point_x - 4, point_y);
}

void GameMap::setRightDown(unsigned int point_x, unsigned int point_y)
{
	setDown(point_x + 1, point_y);
	setDown(point_x + 2, point_y);
	setDown(point_x + 3, point_y);
	setDown(point_x + 4, point_y);
}

void GameMap::setLeftDown(unsigned int point_x, unsigned int point_y)
{
	setDown(point_x - 1, point_y);
	setDown(point_x - 2, point_y);
	setDown(point_x - 3, point_y);
	setDown(point_x - 4, point_y);
}
