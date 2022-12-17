#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Globals.h"
#include "BgWalls.h"
#include "GameMap.h"

class Zombies
{
public:
	Zombies();
	Zombies(sf::RenderWindow &_oknoint, sf::Image &_mapImage, GameMap &gameMap);
	~Zombies();
	void chaseThePlayer(Player &_player, float &frame_time);
	bool zombieBitesPlayer(Player &_player);
	void moveAndDraw(float & _elapsedTime, sf::RenderWindow &_okno);
	bool shootByBullet(Bullet &_bullet);
	bool areAlive();
	void loadTheWalls(sf::Image &_mapImage);
private:
	GameMap* zombiesGroundMap;
	void randVelocity();
	BgWalls bgWalls;
	std::vector <Zombie> vZombies;
	//counter - number of zombie to rand velocity:
	unsigned int nr_zombie = 0;
	sf::Clock randVelocityClock;
};
