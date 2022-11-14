#include "Bullets.h"

Bullets::Bullets()
{
	
}

Bullets::~Bullets()
{
}

void Bullets::fireBullet(const Player &_player)
{
	//if new
	vectorBullets.push_back(Bullet(_player));
	//if there are waiting bullets in secondary vector then:
	//move it to active vector
}

void Bullets::moveAndHit(Zombies &_zombies, float &_elapsedTime, sf::RenderWindow &_okno, char **_tab)
{		//pociski    
	if (!vectorBullets.empty()) {
		int i = 0;
		// vB_it - vectorBullets iterator
		for (auto vB_it = begin(vectorBullets); vB_it != end(vectorBullets); ++vB_it)
		{
			if (_zombies.shootByBullet(*vB_it) || ((vB_it)->is_wall(_tab)))
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
	//for (auto &i : vectorBullets) {
	//	delete &i;						smart pointers - dont need to delete anymore
	//}
	vectorBullets.clear();	//std::forward_list <Bullet*>
}
