#pragma once

#include <vector>
#include "Globals.h"

class Matrix2d
{
public:
	Matrix2d();
	~Matrix2d() = default;
	void setPoint(unsigned int x, unsigned int y);
	bool getPoint(unsigned int x, unsigned int y);
	// getPointFast have no boundary checks!
	bool getPointFast(unsigned int x, unsigned int y);
private:
	bool checkBounds(unsigned int x, unsigned int y);
	std::vector<std::vector<bool>> map2d;
	int mapWidth;
	int mapHeight;
};

