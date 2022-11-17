#include "Matrix2d.h"

Matrix2d::Matrix2d():
	map2d(windowWidth, std::vector<bool>(windowHeight, false)),
	mapWidth(windowWidth),
	mapHeight(windowHeight)
{
}

void Matrix2d::setPoint(int x, int y)
{
	if(checkBounds(x,y))
	{
		map2d[x][y] = 1;
	}
	
}

bool Matrix2d::getPoint(int x, int y)
{
	if (checkBounds(x, y))
	{
		return map2d[x][y];
	}
	return true;
}

bool Matrix2d::checkBounds(int x, int y)
{
	if (x > windowWidth
		or y > windowHeight
		or x < 0
		or y < 0)
	{
		return false;
	}
	return true;
}
