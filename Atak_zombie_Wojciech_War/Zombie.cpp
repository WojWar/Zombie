//#include "stdafx.h"
#include "Zombie.h"


Zombie::Zombie(int points_of_health, sf::Vector2f _pos) :
	RectangleShape()
{
	this->setSize(fsize_of_zombie);

	this->setFillColor(sf::Color(255, 185, 0));
	health = points_of_health;
	bite = false;
	ispixel = false;
	pos_x = pos_y = 0;
	setPosition(_pos);
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
 



void Zombie::collision(const std::vector<RectangleShape> &_vectorObjects, char **_tab, int **_nr_of_object, float fps_time)
{

	ispixel = false;

	 
	for (int i = 0; i< size_of_zombie.x + 1; i++) {

		if (1 == _tab[(int)(this->getPosition().x) + i][(int)(this->getPosition().y)])
		{
			ispixel = true;
			pos_x = (int)(this->getPosition().x) + i;
			pos_y = (int)(this->getPosition().y);
			if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
				numery.push_back(_nr_of_object[pos_x][pos_y]);
			}
		}
		if (1 == _tab[(int)(this->getPosition().x) + i][(int)(this->getPosition().y) + size_of_zombie.y])
		{
			ispixel = true;
			pos_x = (int)(this->getPosition().x) + i;
			pos_y = (int)(this->getPosition().y) + size_of_zombie.y;
			if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
				numery.push_back(_nr_of_object[pos_x][pos_y]);
			}
		}

	}
	for (int j = 0; j< size_of_zombie.y + 1; j++) {
		if (1 == _tab[(int)(this->getPosition().x)][(int)(this->getPosition().y + j)])
		{
			ispixel = true;
			pos_x = (int)(this->getPosition().x);
			pos_y = (int)(this->getPosition().y) + j;
			if (numery.size() == 0 || numery.back() != (_nr_of_object[pos_x][pos_y])) {
				numery.push_back(_nr_of_object[pos_x][pos_y]);
			}
		}
		if (1 == _tab[(int)(this->getPosition().x) + size_of_zombie.x][(int)(this->getPosition().y) + j])
		{
			ispixel = true;
			pos_x = (int)(this->getPosition().x) + size_of_zombie.x;
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
			if (getGlobalBounds().intersects(_vectorObjects[nr].getGlobalBounds())) {
				
				move(-velocity.x * 1000 * fps_time, -velocity.y * 1000 * fps_time);

				//jesli z gory
				if (getPosition().y + getSize().y < _vectorObjects[nr].getPosition().y)
				{
					move(velocity.x * 1000 * fps_time, 0);
					velocity.y = 0;
				}

				//jesli z dolu
				if (getPosition().y > _vectorObjects[nr].getPosition().y + _vectorObjects[nr].getSize().y)
				{
					move(velocity.x * 1000 * fps_time, 0);
					velocity.y = 0;
					//this->setPosition(this->getPosition().x, _vectorObjects[nr].getPosition().y + _vectorObjects[nr].getSize().y);
					
				}

				//jesli z lewej
				if (getPosition().x + size_of_zombie.x < _vectorObjects[nr].getPosition().x)
				{
					//std::cout << "lewa???" << std::endl;
					move(0, velocity.y * 1000 * fps_time);
					if (getPosition().y + getSize().y > _vectorObjects[nr].getPosition().y && getPosition().y + getSize().y < _vectorObjects[nr].getPosition().y + 3)
					{
						position.y = getPosition().y - 2;
						setPosition(getPosition().x, position.y);
					}

					if(getPosition().y>_vectorObjects[nr].getPosition().y)
					velocity.x = -velocity.x;
				}

				//jesli z prawej 
				if (getPosition().x > _vectorObjects[nr].getPosition().x + _vectorObjects[nr].getSize().x)
				{
					//std::cout << "prawa???" << std::endl;
					move(0, velocity.y * 1000 * fps_time);
					if (getPosition().y + getSize().y > _vectorObjects[nr].getPosition().y && getPosition().y + getSize().y < _vectorObjects[nr].getPosition().y + 3)
					{
						position.y = getPosition().y - 2;
						setPosition(getPosition().x, position.y);
					}

					if (getPosition().y>_vectorObjects[nr].getPosition().y)
						velocity.x = -velocity.x;
				}

			}

		}


	}


	numery.clear();
}



void Zombie::collision_wall(BgWalls &_walls)
{
	if (_walls.isWall((int)(this->getPosition().x + size_of_zombie.x/2), (int)(this->getPosition().y)))
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