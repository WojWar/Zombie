#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Zombie.h"
#include "Globals.h"
#include "BgWalls.h"

class Zombies
{
public:
	Zombies();
	Zombies(sf::RenderWindow &_oknoint, const int  &_zombie_health, sf::Image &_mapImage);
	~Zombies();
	void chaseThePlayer(Player &_player, float &frame_time);
	void randVelocity(sf::Clock &clock_for_zombies);
	bool zombieBitesPlayer(Player &_player);
	void moveAndDraw(float & _elapsedTime, const std::vector<sf::RectangleShape>& _vGround, char **_tab, int **_nr_of_object, sf::RenderWindow &_okno);
	bool shootByBullet(Bullet &_bullet);
	bool areAlive();
	void loadTheWalls(sf::Image &_mapImage);
private:
	BgWalls bgWalls;
	std::vector <Zombie> vZombies;
	//licznik - zombie, ktorego predkosc jest losowana:
	unsigned int nr_zombie = 0;
};
