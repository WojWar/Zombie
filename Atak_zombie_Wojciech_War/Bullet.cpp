//#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(const Player &_player):
	RectangleShape(sf::Vector2f(3, 3))
{
	setFillColor(sf::Color::Black);
	setPosition(_player.getPosition().x + 5, _player.getPosition().y + 7);
	if (_player.shooting_direction) {
		velocity.x = 0.2f;
	}
	else {

		velocity.x = -0.2f;
	}

	is_shooted_value = false;

}


Bullet::~Bullet()
{

}


bool Bullet::is_wall(char **_tab)
{
	//check if bullet goes outside of the window size: 
	//it should be stopped when hit the ground or walls, but if its not it will try to read tab values outside of the scope
	int x, y;
	x = (int)getPosition().x;
	y = (int)getPosition().y;

	if ((int)getPosition().x > windowWidth)x = windowWidth;
	if ((int)getPosition().y > windowHeight)y = windowHeight;

	if ((int)getPosition().x <= 0)x = 1;
	if ((int)getPosition().y <= 0)y = 1;

	if (_tab[x][y]) 
	{
		return true; 
	}
	else
	{
		return false;
	}
}

void Bullet::setPosition(float x, float y)
{
	if (x > windowWidth)x = windowWidth;
	if (y > windowHeight)y = windowHeight;

	if (x <= 0)x = 1;
	if (y <= 0)y = 1;

	RectangleShape::setPosition(x, y);
}

