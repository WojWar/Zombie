//#include "stdafx.h"
#include "Zombie.h"


Zombie::Zombie(int points_of_health, sf::Vector2f _pos, GameMap &gameMap) :
	RectangleShape(),
	zombieGroundMap(&gameMap)
{
	this->setSize(fsize_of_zombie);
	this->setFillColor(sf::Color(255, 185, 0));
	this->setOrigin(zombieOffset);
	health = points_of_health;
	bite = false;
	ispixel = false;
	pos_x = pos_y = 0;
	this->setPosition(_pos);
	velocity.y =  velocity.x = 0;
	nr = 0;
}


Zombie::~Zombie()
{
}

void Zombie::randVelocity()
{
	velocity.x = (float)(rand() % 20 - 10);
	velocity.x = velocity.x / 100;

}
void Zombie::randsmallVelocity()
{
	velocity.x = (float)(rand() % 20 - 10);
	velocity.x = velocity.x / 500;

}
 



void Zombie::collision(float fps_time)
{
	sf::Vector2f lastPosition = sf::Vector2f(this->getPosition());
	sf::Vector2f diffPosition = velocity * 1000.0f * fps_time;

	while (zombieGroundMap->isGround(lastPosition + diffPosition))
	{
		if (!zombieGroundMap->isGround(lastPosition + diffPosition - sf::Vector2f(0.0f, 2.0f)))
		{
			diffPosition.y = diffPosition.y - 2.0f;
		}
		else
		{
			diffPosition.x = diffPosition.x / 2;
			diffPosition.y = diffPosition.y / 2;
		}
	}

	sf::Vector2f newPosition = lastPosition + diffPosition;
	this->move(diffPosition);

	//jesli z gory
	if (zombieGroundMap->isGround(newPosition.x, newPosition.y - 5.0f))
	{
		velocity.y = 0;
	}

	//jesli z dolu
	if (zombieGroundMap->isGround(newPosition.x, newPosition.y + 5.0f))
	{
		velocity.y = 0;
	}

	gravityAcceleration(fps_time);
}

void Zombie::gravityAcceleration(float frame_time)
{
	if (!zombieGroundMap->isGround(this->getPosition().x, this->getPosition().y + 3))
	{
		velocity.y += (gravity * 1000 * frame_time);
	}
}

void Zombie::collision_wall(BgWalls &_walls)
{
	if (_walls.isWall((int)(this->getPosition().x), (int)(this->getPosition().y)))
	{
		velocity.x = -velocity.x;
	}
}

void Zombie::race_to_left(float frame_time)
{
	velocity.x = -movespeedZombie * 0.6f;// *600 * frame_time;
}

void Zombie::race_to_right(float frame_time)
{
	velocity.x = movespeedZombie * 0.6f;// 600 * frame_time;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////