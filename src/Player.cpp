
#include "Player.h"

Player::Player(int points_of_health, GameMap &gameMap) :
	health(points_of_health),
	groundMap(&gameMap)
{
	this->setSize(playerSize);
	this->setFillColor(sf::Color::Blue);
	this->setPosition(startPosition);
	this->setOrigin(playerOffset);	
}

Player::Player()
{
	groundMap = nullptr;
	health = 0;
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
	sf::Vector2f diffPosition = velocity * 1000.0f * frame_time;

	while (groundMap->isGround(lastPosition + diffPosition))
	{
		if (!groundMap->isGround(lastPosition + diffPosition - sf::Vector2f(0.0f, 2.0f)))
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

	//from up
	if (groundMap->isGround(newPosition.x, newPosition.y - 1.0f))
	{
		gravitySpeed = 0;
		velocity.y = 0;
	}

	//from down
	if (groundMap->isGround(newPosition.x, newPosition.y + 1.0f))
	{
		gravitySpeed = 0;
		velocity.y = 0;
	}

	if (jump)
	{
		velocity.y = -jumpspeed;
		jump = false;
	}

	//from left
	//if (groundMap.isGround(thisPosition.x - 1, thisPosition.y))
	//{
	//	this->move(0, velocity.y * 1000 * frame_time);
	//}

	////from right
	//if (groundMap.isGround(thisPosition.x + 1, thisPosition.y))
	//{
	//	this->move(0, velocity.y * 1000 * frame_time);
	//}
	gravityAcceleration(frame_time);

	
}

void Player::jumpRequest()
{
	jump = true;
	//velocity.y = -jumpspeed;// *1000 * ElapsedTime;
}


void Player::areClose(const std::vector<Zombie*>& _Objects, float frame_time)
{
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
			}
		}
	}
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

void Player::gravityAcceleration(float frame_time)
{
	bool is = false;
	if (!groundMap->isGround(this->getPosition().x, this->getPosition().y + 1) and (velocity.y < 1.1* jumpspeed))
	{
		is = true;
		velocity.y += (gravity * 1000 * frame_time);
	}
	std::cout << "Gravity: " << (is ? "YES" : "NO ") << "\r";

}
