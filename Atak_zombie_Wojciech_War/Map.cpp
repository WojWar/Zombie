
#include <iostream>
#include "Map.h"
#include "Player.h"

Map::Map(sf::Vector2i playerSize):
	mapName(map_name),
	mapWidth(windowWidth),
	playerOffset(sf::Vector2i(playerSize.x/2, playerSize.y/2)),
	mapHeight(windowHeight)
{
	_mapImage.loadFromFile(mapName);
}

Map::~Map()
{
}

bool Map::isGround(int x, int y)
{
	//std::cout << "x: " << x << ", y: " << y << std::endl;
	return hardGround.getPoint(x, y);
}

bool Map::isGround(float x, float y)
{
	//std::cout << "x: " << x << ", y: " << y << std::endl;
	return hardGround.getPoint((unsigned int)x, (unsigned int)y);
}

bool Map::isGround(sf::Vector2f coordinates)
{
	//std::cout << "x: " << x << ", y: " << y << std::endl;
	return hardGround.getPoint((unsigned int)coordinates.x, (unsigned int)coordinates.y);
}

[[deprecated("Not needed anymore.")]]
void Map::initialise(sf::RenderTexture &_textura) {

	std::cout << std::endl << "Trwa ladowanie mapy." << std::endl;

	bool flag = true;
	for (int i = 0; i < windowWidth; i++) {
		for (int j = 0; j < windowHeight; j++) {
			m_tab[i][j] = 0;
			m_nr_of_object[i][j] = 0;
		}
	}

	//if (!_mapImage.loadFromFile("map_01.png"))

	if (!_mapImage.loadFromFile(mapName))
	{
		std::cout << "Error occured during map loading" << std::endl;
		system("pause");
	}
	_textura.create(windowWidth, windowHeight);

	float constant_x_size = _textura.getSize().x / (float)windowWidth;//windowWidth
	float constant_y_size = _textura.getSize().y / (float)windowHeight;//windowHeight
	float current_x_size;
	float current_y_size;

	sf::RectangleShape shape(sf::Vector2f((float)_textura.getSize().x / windowWidth, (float)_textura.getSize().y / windowHeight));
	shape.setFillColor(sf::Color(139, 69, 19));

	unsigned int temp_i;
	unsigned int temp_k;
	//int add_count = 1;
	for (unsigned int k = 0; k < (unsigned int)windowHeight; k++) {
		for (unsigned int i = 0; i < (unsigned int)windowWidth; i++) {

			shape.setPosition((float)_textura.getSize().x*i / windowWidth, (float)_textura.getSize().y*k / windowHeight);
			if (((sf::Color::Black) == _mapImage.getPixel(i, k)) && (m_tab[i][k] == 0)) {
				m_tab[i][k] = 1;
				m_nr_of_object[i][k] = (int)(groundRectangles.size());
				current_x_size = 0;
				current_y_size = 0;
				temp_i = i;
				temp_k = k;
				while (((sf::Color::Black) == _mapImage.getPixel(temp_i, k) && (temp_i < (unsigned int)windowWidth - 1) && (m_tab[temp_i][k] == 0)) || (temp_i == i)) {
					m_tab[temp_i][k] = 1;
					m_nr_of_object[temp_i][k] = (int)(groundRectangles.size());
					shape.setSize(sf::Vector2f(current_x_size + constant_x_size, current_y_size));
					current_x_size = current_x_size + constant_x_size;
					temp_i++;
				}

				while (flag && (temp_k < (unsigned int)windowHeight - 1)) {
					flag = true;
					for (unsigned int c = i; c < temp_i; c++) {
						if (((sf::Color::Black) == _mapImage.getPixel(c, temp_k) && (m_tab[c][temp_k] == 0)) || (temp_k == k)) {
							m_tab[c][temp_k] = 1;
							m_nr_of_object[c][temp_k] = (int)(groundRectangles.size());
						}
						else
						{
							flag = false;
						}
					}
					if (flag == false) {
						for (unsigned int c = i; c < temp_i; c++) {
							m_tab[c][temp_k] = 0;
							m_nr_of_object[c][temp_k] = 0;
						}
					}

					if (flag == true) {
						shape.setSize(sf::Vector2f(current_x_size, current_y_size + constant_y_size));
						current_y_size = current_y_size + constant_y_size;

						//if (temp_k<ilosc_y)
						temp_k++;
					}
				}

				{
					//std::cout <<"Ladowanie wiersza: "<< k << std::endl;
					_textura.draw(shape);
					groundRectangles.push_back(shape);
				}
				i = temp_i;
				flag = true;
			}

		}
	}


	std::cout << "Ladowanie mapy zakonczone. Ilosc obiektow podloza: " << groundRectangles.size() << std::endl;


}

[[deprecated("Use loadGround() instead.")]]
void Map::loadGroundObjects() {

	std::cout << std::endl << "Loading the ground map" << std::endl;

	bool flag = true;
	for (int i = 0; i < windowWidth; i++) {
		for (int j = 0; j < windowHeight; j++) {
			m_tab[i][j] = 0;
			m_nr_of_object[i][j] = 0;
		}
	}

	if (!_mapImage.loadFromFile(mapName))
	{
		std::cout << "Error occured during map loading" << std::endl;
		system("pause");
	}

	float current_x_size;
	float current_y_size;

	sf::RectangleShape shape(sf::Vector2f(1, 1));
	shape.setFillColor(sf::Color(139, 69, 19));

	unsigned int temp_i;
	unsigned int temp_k;
	//int add_count = 1;
	for (unsigned int k = 0; k < (unsigned int)windowHeight; k++) {
		for (unsigned int i = 0; i < (unsigned int)windowWidth; i++) {

			shape.setPosition((float)i, (float)k);
			if (((sf::Color::Black) == _mapImage.getPixel(i, k)) && (m_tab[i][k] == 0)) {
				m_tab[i][k] = 1;
				m_nr_of_object[i][k] = (int)(groundRectangles.size());
				current_x_size = 1;
				current_y_size = 1;
				temp_i = i;
				temp_k = k;
				while (((sf::Color::Black) == _mapImage.getPixel(temp_i, k) && (temp_i < (unsigned int)windowWidth - 1) && (m_tab[temp_i][k] == 0)) || (temp_i == i)) {
					m_tab[temp_i][k] = 1;
					m_nr_of_object[temp_i][k] = (int)(groundRectangles.size());
					current_x_size++;
					shape.setSize(sf::Vector2f(current_x_size, current_y_size));
					temp_i++;
				}

				while (flag && (temp_k < (unsigned int)windowHeight - 1)) {
					flag = true;
					for (unsigned int c = i; c < temp_i; c++) {
						if (((sf::Color::Black) == _mapImage.getPixel(c, temp_k) && (m_tab[c][temp_k] == 0)) || (temp_k == k)) {
							m_tab[c][temp_k] = 1;
							m_nr_of_object[c][temp_k] = (int)(groundRectangles.size());
						}
						else
						{
							flag = false;
						}
					}
					if (flag == false) {
						for (unsigned int c = i; c < temp_i; c++) {
							m_tab[c][temp_k] = 0;
							m_nr_of_object[c][temp_k] = 0;
						}
					}

					if (flag == true) {
						current_y_size++;
						shape.setSize(sf::Vector2f(current_x_size, current_y_size));

						//if (temp_k<ilosc_y)
						temp_k++;
					}
				}

				{
					groundRectangles.push_back(shape);
				}
				i = temp_i;
				flag = true;
			}

		}
	}


	std::cout << "Ground map loading finished." << std::endl;


}


void Map::loadGround()
{
	std::cout << std::endl << "Loading the ground map" << std::endl;
	int hOffset = playerOffset.x;
	int vOffset = playerOffset.y;

	sf::Vector2u imageSize = _mapImage.getSize();

	for (unsigned int y = 0; y < (unsigned int)windowHeight - 1; y++) {
		for (unsigned int x = 0; x < (unsigned int)windowWidth - 1; x++) {
			//if (getPoint(x, y)) 
			//{
			//	hardGround.setPoint(x, y);
			//}
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

	 //hardGround.setPoint(x, y);
	//std::cout << "Ground map loading: x: " << x << ", y: " << y <<   std::endl;

	

	std::cout << "Ground map loading finished." << std::endl;
}

bool Map::imageGetPoint(unsigned int point_x, unsigned int point_y)
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

void Map::setUp(unsigned int point_x, unsigned int point_y)
{
	hardGround.setPoint(point_x, point_y + 1);
	hardGround.setPoint(point_x, point_y + 2);
	hardGround.setPoint(point_x, point_y + 3);
	hardGround.setPoint(point_x, point_y + 4);
	hardGround.setPoint(point_x, point_y + 5);
	hardGround.setPoint(point_x, point_y + 6);
}

void Map::setDown(unsigned int point_x, unsigned int point_y)
{
	hardGround.setPoint(point_x, point_y - 1);
	hardGround.setPoint(point_x, point_y - 2);
	hardGround.setPoint(point_x, point_y - 3);
	hardGround.setPoint(point_x, point_y - 4);
	hardGround.setPoint(point_x, point_y - 5);
	hardGround.setPoint(point_x, point_y - 6);
}

void Map::setRight(unsigned int point_x, unsigned int point_y)
{
	hardGround.setPoint(point_x + 1, point_y);
	hardGround.setPoint(point_x + 2, point_y);
	hardGround.setPoint(point_x + 3, point_y);
	hardGround.setPoint(point_x + 4, point_y);
}

void Map::setLeft(unsigned int point_x, unsigned int point_y)
{
	hardGround.setPoint(point_x - 1, point_y);
	hardGround.setPoint(point_x - 2, point_y);
	hardGround.setPoint(point_x - 3, point_y);
	hardGround.setPoint(point_x - 4, point_y);
}

void Map::setRightUp(unsigned int point_x, unsigned int point_y)
{
	setUp(point_x + 1, point_y);
	setUp(point_x + 2, point_y);
	setUp(point_x + 3, point_y);
	setUp(point_x + 4, point_y);
}

void Map::setLeftUp(unsigned int point_x, unsigned int point_y)
{
	setUp(point_x - 1, point_y);
	setUp(point_x - 2, point_y);
	setUp(point_x - 3, point_y);
	setUp(point_x - 4, point_y);
}

void Map::setRightDown(unsigned int point_x, unsigned int point_y)
{
	setDown(point_x + 1, point_y);
	setDown(point_x + 2, point_y);
	setDown(point_x + 3, point_y);
	setDown(point_x + 4, point_y);
}

void Map::setLeftDown(unsigned int point_x, unsigned int point_y)
{
	setDown(point_x - 1, point_y);
	setDown(point_x - 2, point_y);
	setDown(point_x - 3, point_y);
	setDown(point_x - 4, point_y);
}
