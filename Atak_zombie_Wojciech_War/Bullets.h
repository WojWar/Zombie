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
	void moveAndHit(Zombies &_zombies, float &_elapsedTime, sf::RenderWindow &_okno, char **_tab);
	void clearMemory();
private:
	//active bullets
	std::forward_list <std::unique_ptr<Bullet>> vectorBullets;
	//inactive bullets
	std::forward_list <Bullet*> vectorWaitingBullets;
	//std::unique_ptr<Bullet> unibull;
};

