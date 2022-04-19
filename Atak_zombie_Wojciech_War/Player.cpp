//#include "stdafx.h"
#include "Player.h"


Player::Player(int points_of_health) :
	RectangleShape(sf::Vector2f(10, 15))
{
	size_of_player_x = 10;
	size_of_player_y = 15;
	this->setFillColor(sf::Color::Blue);

	this->setPosition(50, 400);
	jumpCounter = 0;
	intersectsSomething = false;
	health = points_of_health;
	bites_me = false;
	ispixel = false;
	pos_x = 50;
	pos_y = 400;
	shooting_direction = true;
	nr = 0;
}


Player::~Player()
{
}


void Player::collision(const std::vector<RectangleShape> &_vectorObjects, char **_tab, int **_nr_of_object, float frame_time)
{
	ispixel = true;
	while (ispixel)
	{
		ispixel = false;

		for (int i = 0; i < size_of_player_x + 1; i++) {

			if (1 == _tab[(int)(this->getPosition().x) + i][(int)(this->getPosition().y)])
			{
				ispixel = true;
				pos_x = (int)(this->getPosition().x) + i;
				pos_y = (int)(this->getPosition().y);
				if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
					numery.push_back(_nr_of_object[pos_x][pos_y]);
				}
			}
			if (1 == _tab[(int)(this->getPosition().x) + i][(int)(this->getPosition().y) + size_of_player_y])
			{
				ispixel = true;
				pos_x = (int)(this->getPosition().x) + i;
				pos_y = (int)(this->getPosition().y) + size_of_player_y;
				if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
					numery.push_back(_nr_of_object[pos_x][pos_y]);
				}
			}

		}
		for (int j = 0; j < size_of_player_y + 1; j++) {
			if (1 == _tab[(int)(this->getPosition().x)][(int)(this->getPosition().y + j)])
			{
				ispixel = true;
				pos_x = (int)(this->getPosition().x);
				pos_y = (int)(this->getPosition().y) + j;
				if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
					numery.push_back(_nr_of_object[pos_x][pos_y]);
				}
			}
			if (1 == _tab[(int)(this->getPosition().x) + size_of_player_x][(int)(this->getPosition().y) + j])
			{
				ispixel = true;
				pos_x = (int)(this->getPosition().x) + size_of_player_x;
				pos_y = (int)(this->getPosition().y) + j;
				if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
					numery.push_back(_nr_of_object[pos_x][pos_y]);
				}
			}

		}

		if (ispixel)
		{

			for (unsigned int i = 0; i < numery.size(); i++) {
				nr = numery[i];
				if (this->getGlobalBounds().intersects(_vectorObjects[nr].getGlobalBounds())) {


					this->move(-velocity.x * 1000 * frame_time, -velocity.y * 1000 * frame_time);

					//jesli z gory
					if (this->getPosition().y + this->getSize().y < _vectorObjects[nr].getPosition().y)
					{
						this->move(velocity.x * 1000 * frame_time, 0);
						velocity.y = 0;
						intersectsSomething = true;
					}

					//jesli z dolu
					if (this->getPosition().y > _vectorObjects[nr].getPosition().y + _vectorObjects[nr].getSize().y)
					{
						this->move(velocity.x * 1000 * frame_time, 0);
						velocity.y = 0;
						//this->setPosition(this->getPosition().x, _vectorObjects[nr].getPosition().y + _vectorObjects[nr].getSize().y);

					}

					//jesli z lewej
					if (this->getPosition().x + size_of_player_x < _vectorObjects[nr].getPosition().x)
					{
						//std::cout << "lewa???" << std::endl;
						this->move(0, velocity.y * 1000 * frame_time);
						intersectsSomething = true;
						if (this->getPosition().y + this->getSize().y > _vectorObjects[nr].getPosition().y && this->getPosition().y + this->getSize().y < _vectorObjects[nr].getPosition().y + 3)
						{
							pos.y = this->getPosition().y - 2;
							this->setPosition(this->getPosition().x, pos.y);
						}

					}

					//jesli z prawej od playera jest kolizja
					if (this->getPosition().x > _vectorObjects[nr].getPosition().x + _vectorObjects[nr].getSize().x)
					{
						//std::cout << "prawa???" << std::endl;
						this->move(0, velocity.y * 1000 * frame_time);
						intersectsSomething = true;
						if (this->getPosition().y + this->getSize().y > _vectorObjects[nr].getPosition().y && this->getPosition().y + this->getSize().y < _vectorObjects[nr].getPosition().y + 3)
						{
							pos.y = this->getPosition().y - 2;
							this->setPosition(this->getPosition().x, pos.y);
						}

					}


				}

			}


		}

		numery.clear();
	}

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

bool Player::zombie_bites_player(const std::vector<Zombie*>& _Objects)
{
	bites_me = false;
	for (unsigned int i = 0; i < _Objects.size(); i++) {

		if ((this->getGlobalBounds().intersects(_Objects[i]->getGlobalBounds()))&&(_Objects[i]->bite ==false)) {
			_Objects[i]->bite = true;
			bites_me = true;
			health--;
			std::cout << (int)(health) << std::endl;
		}

	}
	return bites_me;
}

void Player::gravity_acceleration(float _gravity,float _jumpspeed)
{
	if ((velocity.y<1.1* _jumpspeed))
		velocity.y += _gravity;
}
