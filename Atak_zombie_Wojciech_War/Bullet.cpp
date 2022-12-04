//#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(const Player &_player):
	RectangleShape(sf::Vector2f(3, 3))
{
	setFillColor(sf::Color::Black);
	setPosition(_player.getPosition());
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

	if (x > (unsigned int)windowWidth
		or y > (unsigned int)windowHeight
		or _tab[x][y])
	{
		//velocity.x = velocity.y = 0;
		return true;
	}
	return false;
}

void Bullet::setPosition(sf::Vector2f pos)
{
	if (pos.x > windowWidth)pos.x = (float)windowWidth;
	if (pos.y > windowHeight)pos.y = (float)windowHeight;

	if (pos.x <= 0)pos.x = 1.0f;
	if (pos.y <= 0)pos.y = 1.0f;

	RectangleShape::setPosition(pos);
}

