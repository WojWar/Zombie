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
}


Bullet::~Bullet()
{

}


bool Bullet::is_wall(char **_tab)
{
	//check if bullet goes outside of the window size: 
	//it should be stopped when hit the ground or walls, but if its not it will try to read tab values outside of the scope
	unsigned int x = (unsigned int)getPosition().x;
	unsigned int y = (unsigned int)getPosition().y;

	if (x > windowWidth
		or y > windowHeight
		or _tab[x][y])
	{
		//velocity.x = velocity.y = 0;
		return true;
	}
	return false;
}

void Bullet::setPosition(float x, float y)
{
	if (x > windowWidth)x = windowWidth;
	if (y > windowHeight)y = windowHeight;

	if (x <= 0)x = 1;
	if (y <= 0)y = 1;

	RectangleShape::setPosition(x, y);
}

