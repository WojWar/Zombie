//#include "stdafx.h"
#include "Player.h"


Player::Player(int points_of_health) :
	RectangleShape(sf::Vector2f(10, 14)),
	health(points_of_health)
{
	this->setFillColor(sf::Color::Blue);
	this->setPosition(50, 400);
	this->setOrigin(playerOffset);
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


	sf::Vector2f lastPosition = sf::Vector2f(this->getPosition());

	sf::Vector2f diffPosition = sf::Vector2f(this->getPosition());

	this->move(velocity * 1000.0f * frame_time);

	sf::Vector2f newPosition = sf::Vector2f(this->getPosition());

	//sf::Vector2i thisPosition = sf::Vector2i((int)(this->getPosition().x), (int)(this->getPosition().y));

	//get out of collision
	float diffx = newPosition.x - lastPosition.x;
	float diffy = newPosition.y - lastPosition.y;
	while (groundMap.isGround(newPosition.x, newPosition.y))
	{
		if (diffx > 0)
		{
			newPosition.x--;
		}
		if (diffy > 0)
		{
			newPosition.y--;
		}
		if (diffx < 0)
		{
			newPosition.x++;
		}
		if (diffy < 0)
		{
			newPosition.y++;
		}

	}
	this->setPosition(sf::Vector2f(newPosition));


	//jesli z gory
	if (groundMap.isGround(newPosition.x, newPosition.y - 1))
	{
		gravitySpeed = 0;
		velocity.y = 0;
	}

	//jesli z dolu
	if (groundMap.isGround(newPosition.x, newPosition.y + 1))
	{
		gravitySpeed = 0;
		velocity.y = 0;
		//while (groundMap.isGround(newPosition.x, newPosition.y))
		//{
		//	this->move(0, -1);
		//	thisPosition = sf::Vector2i(this->getPosition()) + playerOffset;
		//}
	}

	if (jump)
	{
		velocity.y = -jumpspeed;
		jump = false;
	}
	//jesli z lewej
	//if (groundMap.isGround(thisPosition.x - 1, thisPosition.y))
	//{
	//	this->move(0, velocity.y * 1000 * frame_time);

	//}

	////jesli z prawej od playera jest kolizja
	//if (groundMap.isGround(thisPosition.x + 1, thisPosition.y))
	//{
	//	this->move(0, velocity.y * 1000 * frame_time);


	//}
	gravity_acceleration(frame_time);

	
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

void Player::gravity_acceleration(float frame_time)
{
	if ((velocity.y <1.1* jumpspeed))
		velocity.y += (gravity * 1000 * frame_time);
}
