//#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(const Player &_player):
	RectangleShape(sf::Vector2f(3, 3))
{
	setFillColor(sf::Color::Black);
	setPosition(_player.getPosition().x + 5, _player.getPosition().y + 7);
	if (_player.shooting_direction) {
		velocity.x = 0.3f;
	}
	else {

		velocity.x = -0.3f;
	}

	is_shooted_value = false;

}


Bullet::~Bullet()
{

}


bool Bullet::is_wall(char _tab[][576])
{
	if (_tab[(int)(getPosition().x)][(int)(getPosition().y)]) 
	{
		return true; 
	}
	else
	{
		return false;
	}
}

bool Bullet::is_zombie(std::vector<Zombie*> &_vectorZombies)
{
		for (unsigned int i = 0; i < _vectorZombies.size(); i++) {
			if (_vectorZombies[i]->getGlobalBounds().contains(getPosition()))
			{
				_vectorZombies[i]->health--;
				is_shooted_value = true;

				if (_vectorZombies[i]->health <1) {
					delete _vectorZombies[i];
					_vectorZombies.erase(_vectorZombies.begin() + i);
				}
			}
		}
		return	is_shooted_value; 
}
