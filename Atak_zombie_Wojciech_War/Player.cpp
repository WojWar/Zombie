//#include "stdafx.h"
#include "Player.h"


Player::Player(int points_of_health) :
	RectangleShape(sf::Vector2f(10, 14)),
	health(points_of_health)
{
	this->setFillColor(sf::Color::Blue);

	this->setPosition(50, 400);
	pos_x = 50;
	pos_y = 400;

	groundMap.loadGround();
	
}

Player::Player()
{
}


Player::~Player()
{
}


sf::Vector2i Player::getSize()
{
	return sf::Vector2i(size_of_player_x, size_of_player_y);
}


void Player::performMove(float frame_time)
{

	gravity_acceleration();

	ispixel = true;
	sf::Vector2i thisPosition = sf::Vector2i((int)(this->getPosition().x), (int)(this->getPosition().y));
	
	ispixel = groundMap.isGround(thisPosition.x, thisPosition.y);

	std::cout << "position:  " << ispixel << std::endl;

	//jesli z gory
	if (groundMap.isGround(thisPosition.x, thisPosition.y - 1))
	{
		//velocity.y = 0;
		intersectsSomething = true;
	}

	//jesli z dolu
	if (groundMap.isGround(thisPosition.x, thisPosition.y + 1))
	{
		if (jump)
		{
			velocity.y = -jumpspeed;
			jump = false;
		}
		else
			velocity.y = 0;
	}

	//jesli z lewej
	if (groundMap.isGround(thisPosition.x - 1, thisPosition.y))
	{
		this->move(0, velocity.y * 1000 * frame_time);

	}

	//jesli z prawej od playera jest kolizja
	if (groundMap.isGround(thisPosition.x + 1, thisPosition.y))
	{
		this->move(0, velocity.y * 1000 * frame_time);


	}

	this->move(velocity.x * 1000 * frame_time, velocity.y * 1000 * frame_time);
}

void Player::jumpRequest()
{
	jump = true;
	//velocity.y = -jumpspeed;// *1000 * ElapsedTime;
}

void Player::are_close(const std::vector<Zombie*>& _Objects, float frame_time)
{
	//bool is = false;

	for (unsigned int i = 0; i < _Objects.size(); i++) {

		if ((_Objects[i]->getPosition().x - pos.x < 100) && (_Objects[i]->getPosition().x - pos.x > -100)) {
			if ((_Objects[i]->getPosition().y - pos.y < 100) && (_Objects[i]->getPosition().y - pos.y > -100)) {
				if (_Objects[i]->getPosition().x > pos.x) {
					_Objects[i]->race_to_left(frame_time);
				}
				else
				{
					_Objects[i]->race_to_right(frame_time);
				}
				//is = true;
			}
		}

	} 
	//return is;
}

bool Player::isAlive()
{
	return (bool)health;
}

void Player::loseOneLivePoint()
{
	health--;
	std::cout << "player live points: " << health << std::endl;
}

void Player::gravity_acceleration()
{
	if ((gravitySpeed <1.1* jumpspeed))
		gravitySpeed += gravity;
}
