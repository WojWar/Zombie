#pragma once
#include <forward_list>
#include <vector>
#include "Bullet.h"
#include "Zombies.h"
class Bullets
{
public:
	Bullets();
	~Bullets();
	void fireBullet(const Player &_player);
	void moveAndHit(Zombies &_zombies, float &_elapsedTime, sf::RenderWindow &_okno, char _tab[][576]);
	void clearMemory();
private:
	std::forward_list <Bullet*> vectorBullets;
};

