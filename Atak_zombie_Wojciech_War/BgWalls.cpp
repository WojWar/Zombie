#include "BgWalls.h"

BgWalls::BgWalls() :
	wallsMapWidth(windowWidth),
	wallsMapHeight(windowHeight),
	map2d(windowWidth, std::vector<bool>(windowHeight, false))
{	
}

void BgWalls::Init(sf::Image &_mapImage)
{
	std::cout << std::endl << "Trwa ladowanie scian." << std::endl;

	int walls_count = 0;

	for (int k = 1; k < windowHeight; k++) {
		for (int i = 1; i < windowWidth; i++) {

			if ((Color::Red) == _mapImage.getPixel(i, k)) {
				map2d[i][k] = 1;
				if (!map2d[i-1][k] and !map2d[i][k-1])
				{
					walls_count++;
				}
			}
		}
	}

	std::cout << "Ladowanie scian zakonczone. Ilosc obiektow scian: " << walls_count << std::endl << std::endl;

}

bool BgWalls::isWall(int x, int y)
{
	if (x<0 or y<0 or x>wallsMapWidth or y>wallsMapHeight)
	{
		std::cout << "BgWalls: ERROR cordinates out of range x: " <<x<<", y: "<<y << std::endl << std::endl;
		return false;
	}
	if (map2d[x][y])
	{
		return true;
	}
	return false;
}

BgWalls::~BgWalls()
{

}
