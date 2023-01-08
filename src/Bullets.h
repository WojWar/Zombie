#pragma once
#include <forward_list>
#include <vector>
#include "Bullet.h"
#include "Zombies.h"
#include "GameMap.h"
class Bullets
{
public:
	Bullets(GameMap &gameMap);
	~Bullets();
	void fireBullet(const Player &_player);
	void moveAndHit(Zombies &_zombies, float &_elapsedTime, sf::RenderWindow &_okno);
	void clearMemory();
private:
	GameMap* bulletsGroundMap;
	std::vector <Bullet> vectorBullets;
};

