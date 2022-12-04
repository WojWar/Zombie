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

	//void initialise(sf::RenderTexture &_textura);
	//void loadGroundObjects();
	void loadGround();
private:
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
	sf::Vector2i playerOffset;
	int mapWidth;
	int mapHeight;
	std::string mapName;

	//mapa:
	sf::Image _mapImage;

	//tablice dla podloza:
	//char **m_tab; // tutaj wartosc 0 lub 1 czy jest grunt
	//int **m_nr_of_object; // tutaj nr obiektu w vectorze ktory jest w danym pixelu

	//podloze i sciany ograniczajace:
	//std::vector <sf::RectangleShape> groundRectangles;
	Matrix2d hardGround;
	//std::vector<std::vector<bool>> map2d;


};

