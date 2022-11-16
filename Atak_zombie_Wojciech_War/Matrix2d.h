#pragma once

#include <vector>
#include "Globals.h"

class Matrix2d
{
public:
	Matrix2d();
	~Matrix2d() = default;
	void setPoint(int x, int y);
	bool getPoint(int x, int y);
private:
	bool checkBounds(int x, int y);
	std::vector<std::vector<bool>> map2d;
	int mapWidth;
	int mapHeight;
};

