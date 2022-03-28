//#include "stdafx.h"
#include "Zombie.h"


Zombie::Zombie(int points_of_health, sf::Vector2f _pos):
	RectangleShape(sf::Vector2f(5,10))
{
	size_of_player_x = 5;
	size_of_player_y = 10;
	this->setFillColor(sf::Color(255, 185, 0));
	health = points_of_health;
	bite = false;
	ispixel = false;
	pos_x = pos_y = 0;
	setPosition(_pos);
	velocity.y =  velocity.x = 0;
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
 



void Zombie::collision(const std::vector<RectangleShape> &_vectorObjects, char _tab[][576], int _nr_of_object[][576],float fps_time)
{

	ispixel = false;

	 
/*
		if (1 == _tab[(int)(this->getPosition().x)][(int)(this->getPosition().y)])
		{
			ispixel = true;
			pos_x = (int)(this->getPosition().x) ;
			pos_y = (int)(this->getPosition().y);
			if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
				numery.push_back(_nr_of_object[pos_x][pos_y]);
			}
		}
		if (1 == _tab[(int)(this->getPosition().x) ][(int)(this->getPosition().y) + size_of_player_y])
		{
			ispixel = true;
			pos_x = (int)(this->getPosition().x) ;
			pos_y = (int)(this->getPosition().y) + size_of_player_y;
			if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
				numery.push_back(_nr_of_object[pos_x][pos_y]);
			}
		}

	
	
		if (1 == _tab[(int)(this->getPosition().x) + size_of_player_x][(int)(this->getPosition().y )])
		{
			ispixel = true;
			pos_x = (int)(this->getPosition().x + size_of_player_x);
			pos_y = (int)(this->getPosition().y) ;
			if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
				numery.push_back(_nr_of_object[pos_x][pos_y]);
			}
		}
		if (1 == _tab[(int)(this->getPosition().x) + size_of_player_x][(int)(this->getPosition().y) + size_of_player_y])
		{
			ispixel = true;
			pos_x = (int)(this->getPosition().x) + size_of_player_x;
			pos_y = (int)(this->getPosition().y) + size_of_player_y;
			if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
				numery.push_back(_nr_of_object[pos_x][pos_y]);
			}
		}
*/
	

	for (int i = 0; i<size_of_player_x + 1; i++) {

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
	for (int j = 0; j<size_of_player_y + 1; j++) {
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
				
				this->move(-velocity.x * 1000 * fps_time, -velocity.y * 1000 * fps_time);

				//jesli z gory
				if (this->getPosition().y + this->getSize().y < _vectorObjects[nr].getPosition().y)
				{
					this->move(velocity.x * 1000 * fps_time, 0);
					velocity.y = 0;
					intersectsSomething = true;
				}

				//jesli z dolu
				if (this->getPosition().y > _vectorObjects[nr].getPosition().y + _vectorObjects[nr].getSize().y)
				{
					this->move(velocity.x * 1000 * fps_time, 0);
					velocity.y = 0;
					//this->setPosition(this->getPosition().x, _vectorObjects[nr].getPosition().y + _vectorObjects[nr].getSize().y);
					intersectsSomething = true;
				}

				//jesli z lewej
				if (this->getPosition().x + size_of_player_x < _vectorObjects[nr].getPosition().x)
				{
					//std::cout << "lewa???" << std::endl;
					this->move(0, velocity.y * 1000 * fps_time);
					intersectsSomething = true;
					if (this->getPosition().y + this->getSize().y > _vectorObjects[nr].getPosition().y && this->getPosition().y + this->getSize().y < _vectorObjects[nr].getPosition().y + 3)
					{
						position.y = this->getPosition().y - 2;
						this->setPosition(this->getPosition().x, position.y);
					}

					if(this->getPosition().y>_vectorObjects[nr].getPosition().y)
					velocity.x = -velocity.x;
				}

				//jesli z prawej 
				if (this->getPosition().x > _vectorObjects[nr].getPosition().x + _vectorObjects[nr].getSize().x)
				{
					//std::cout << "prawa???" << std::endl;
					this->move(0, velocity.y * 1000 * fps_time);
					intersectsSomething = true;
					if (this->getPosition().y + this->getSize().y > _vectorObjects[nr].getPosition().y && this->getPosition().y + this->getSize().y < _vectorObjects[nr].getPosition().y + 3)
					{
						position.y = this->getPosition().y - 2;
						this->setPosition(this->getPosition().x, position.y);
					}

					if (this->getPosition().y>_vectorObjects[nr].getPosition().y)
						velocity.x = -velocity.x;
				}

			}

		}


	}


	numery.clear();
}



void Zombie::collision_wall(char _tab[][576])
{

	ispixel = false;

	 
	for (int j = 0; j<size_of_player_y + 1; j++) {
		if (1 == _tab[(int)(this->getPosition().x)][(int)(this->getPosition().y + j)])
		{
			ispixel = true;
		}
		if (1 == _tab[(int)(this->getPosition().x) + size_of_player_x][(int)(this->getPosition().y) + j])
		{
			ispixel = true;
		}

	}
	if (ispixel)
	{
		velocity.x = -velocity.x; 
	}
}

void Zombie::race_to_left(float frame_time)
{
	velocity.x = -movespeed * 0.6f;// *600 * frame_time;
}

void Zombie::race_to_right(float frame_time)
{
	velocity.x = movespeed * 0.6f;// 600 * frame_time;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////