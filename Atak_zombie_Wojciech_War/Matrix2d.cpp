
#include <iostream>
#include "Matrix2d.h"

Matrix2d::Matrix2d():
	map2d(mwindowHeight, std::vector<bool>(mwindowWidth, false))
{
}

Matrix2d::~Matrix2d()
{
}

void Matrix2d::setPoint(unsigned int x, unsigned int y)
{
	if(!getPoint(x,y))
	{
		map2d.at(y).at(x) = true;
		//printf("setPoint");
	}
	
}

bool Matrix2d::getPointFast(unsigned int x, unsigned int y)
{
	return map2d[x][y];
}

bool Matrix2d::getPoint(unsigned int x, unsigned int y)
{
	try {
		return map2d.at((size_t)y).at((size_t)x);
	}
	catch (const std::out_of_range& ) 
	{
		std::cout << "matrix2d out of range y: " << y << ", x: " << x << "\r";
		return true;
	}
}

bool Matrix2d::getPoint(sf::Vector2f coords)
{
	try {
		return map2d.at((size_t)coords.y).at((size_t)coords.x);
	}
	catch (const std::out_of_range&)
	{
		std::cout << "matrix2d out of range y: " << coords.y << ", x: " << coords.x << "\r";
		return true;
	}
}
