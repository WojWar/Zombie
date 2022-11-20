#include "Matrix2d.h"

Matrix2d::Matrix2d():
	map2d(windowWidth, std::vector<bool>(windowHeight, false)),
	mapWidth(windowWidth),
	mapHeight(windowHeight)
{
}

void Matrix2d::setPoint(unsigned int x, unsigned int y)
{
	if(checkBounds(x,y))
	{
		map2d[x][y] = true;
	}
	
}

bool Matrix2d::getPoint(unsigned int x, unsigned int y)
{
	if (checkBounds(x, y))
	{
		return map2d[x][y];
	}
	return true;
}

bool Matrix2d::getPointFast(unsigned int x, unsigned int y)
{
	return map2d[x][y];
}

bool Matrix2d::checkBounds(unsigned int x, unsigned int y)
{
	if (x > map2d.size()-1 or y > map2d[x].size()-1)
	{
		return false;
	}
	return true;
}
