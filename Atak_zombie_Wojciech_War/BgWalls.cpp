#include "BgWalls.h"

BgWalls::BgWalls() :
	wallsMapWidth(windowWidth),
	wallsMapHeight(windowHeight),
	map2d(windowWidth, std::vector<bool>(windowHeight, false))
{	
}

void BgWalls::Init(sf::Image &_mapImage)
{
	std::cout << std::endl << "BgWalls: Loading walls for zombies.." << std::endl;

	for (int k = 2; k < windowHeight-2; k++) {
		for (int i = 2; i < windowWidth-2; i++) {

			if ((Color::Red) == _mapImage.getPixel(i, k)) {
				map2d[i][k] = 1;
				map2d[i-1][k] = 1;
				map2d[i-2][k] = 1;
				map2d[i+1][k] = 1;
				map2d[i+2][k] = 1;
				if (!map2d[i-1][k] and !map2d[i][k-1])
				{
					walls_count++;
				}
			}
		}
	}
	std::cout << "BgWalls: Walls for zombies loaded. Count: " << walls_count << std::endl << std::endl;
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
