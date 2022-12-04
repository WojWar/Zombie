#pragma once

#include <SFML/Graphics.hpp>
#include <array>

const int mwindowHeight = 576;
const int mwindowWidth = 1024;

class Matrix2d
{
public:
	Matrix2d();
	~Matrix2d();
	void setPoint(unsigned int x, unsigned int y);
	bool getPoint(unsigned int x, unsigned int y);
	bool getPoint(sf::Vector2f coords);
	// getPointFast have no boundary checks!
	bool getPointFast(unsigned int x, unsigned int y);
	std::array<std::array<bool, mwindowWidth>, mwindowHeight> map2d{}; //zero initialized array

};

