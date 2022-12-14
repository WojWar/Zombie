#include "Zombies.h"

Zombies::Zombies()
{
	zombiesGroundMap = nullptr;
}

Zombies::Zombies(sf::RenderWindow &_oknoint, const int  &_zombie_health, sf::Image &_mapImage, GameMap &gameMap) :
	zombiesGroundMap(&gameMap)
{
	
	for (int k = 0; k < windowHeight; k++) {
		for (int i = 0; i < windowWidth; i++) {
			if ((sf::Color::Blue) == _mapImage.getPixel(i, k)) {
				vZombies.push_back(Zombie(_zombie_health, sf::Vector2f((float)i, (float)k), *zombiesGroundMap));

				vZombies.back().randsmallVelocity(); // losuje predkosc w poziomie
			}
		}
	}
	randVelocityClock.restart();
}

Zombies::~Zombies()
{

}

void Zombies::chaseThePlayer(Player & _player, float & frame_time)
{
	for (unsigned int i = 0; i < vZombies.size(); i++) {

		if ((vZombies[i].getPosition().x - _player.pos.x < 100) && (vZombies[i].getPosition().x - _player.pos.x > -100)) {
			if ((vZombies[i].getPosition().y - _player.pos.y < 100) && (vZombies[i].getPosition().y - _player.pos.y > -100)) {
				if (vZombies[i].getPosition().x > _player.pos.x) {
					vZombies[i].race_to_left(frame_time);
				}
				else
				{
					vZombies[i].race_to_right(frame_time);
				}
			}
		}

	}
}

void Zombies::randVelocity()
{
	//losowanie predkosci i kierunku zombie, co 0.15 sekundy kolejny zombie
	if (randVelocityClock.getElapsedTime().asMilliseconds() > 150) {
		nr_zombie++;
		if (!(nr_zombie < vZombies.size())) nr_zombie = 0;
		vZombies[nr_zombie].randVelocity();
		randVelocityClock.restart();
	}
}

bool Zombies::zombieBitesPlayer(Player & _player)
{
	for (unsigned int i = 0; i < vZombies.size(); i++) {

		if ((_player.getGlobalBounds().intersects(vZombies[i].getGlobalBounds())) && (vZombies[i].bite == false)) {
			vZombies[i].bite = true;
			_player.loseOneLivePoint();
			return true;
		}
	}
	return false;
}

void Zombies::moveAndDraw(float & _elapsedTime, sf::RenderWindow &_okno)
{
	this->randVelocity();
	for (unsigned int i = 0; i < vZombies.size(); i++) {

		if (vZombies[i].health < 1) {
			vZombies.erase(vZombies.begin() + i);
			break;
		}



		//odbicia od czerwonych scian:
		vZombies[i].collision_wall(bgWalls);

		//kolizja z podlozem:
		vZombies[i].collision(_elapsedTime);

		_okno.draw(vZombies[i]);
	}
}

bool Zombies::shootByBullet(Bullet &_bullet)
{
	for (std::vector<Zombie>::iterator i = vZombies.begin(); i != vZombies.end(); ) {
		if ((*i).getGlobalBounds().contains(_bullet.getPosition()))
		{
			(*i).health--;
			return true;
		}
		++i;
	}
	return false;
}

bool Zombies::areAlive()
{
	return (bool)vZombies.size();
}

void Zombies::loadTheWalls(sf::Image & _mapImage)
{
	bgWalls.Init(_mapImage);
}
