#include "Bullets.h"

Bullets::Bullets(GameMap &gameMap) :
	bulletsGroundMap(&gameMap)
{
}

Bullets::~Bullets()
{
	clearMemory();
}

void Bullets::fireBullet(const Player &_player)
{
	vectorBullets.push_back(Bullet(_player));
}

void Bullets::moveAndHit(Zombies &_zombies, float &_elapsedTime, sf::RenderWindow &_okno)
{    
	if (!vectorBullets.empty()) {
		int i = 0;
		// vB_it - vectorBullets iterator
		for (auto vB_it = begin(vectorBullets); vB_it != end(vectorBullets); ++vB_it)
		{
			if (_zombies.shootByBullet(*vB_it) || (bulletsGroundMap->isGround(vB_it->getPosition())))
			{
				vectorBullets.erase(vB_it);
				break;
			}
			else
			{
				(vB_it)->move(((*vB_it).velocity.x) * 1000 * _elapsedTime, ((*vB_it).velocity.y) * 1000 * _elapsedTime);
				_okno.draw((*vB_it));
			}
			i++;
		}

		std::cout << "vectorBullets: " << i << std::endl;
	}
}

void Bullets::clearMemory()
{
	vectorBullets.clear();
}
