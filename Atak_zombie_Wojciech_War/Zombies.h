#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Globals.h"

class Zombies
{
public:
	Zombies();
	Zombies(sf::RenderWindow &_oknoint, const int  &_zombie_health, sf::Image &_mapImage);
	~Zombies();
	int size();
	void chaseThePlayer(Player &_player, float &frame_time);
	void randVelocity(sf::Clock &clock_for_zombies);
	bool zombieBitesPlayer(Player &_player);
	void moveAndDraw(float & _elapsedTime, const std::vector<sf::RectangleShape>& _vGround, char _tabRed[][576], char _tab[][576], int _nr_of_object[][576], sf::RenderWindow &_okno);
	bool shootByBullet(Bullet &_bullet);

	std::vector <Zombie*> vZombies;
private:

	//licznik - zombie, ktorego predkosc jest losowana:
	unsigned int nr_zombie = 0;
};
