#include "Zombies.h"

Zombies::Zombies()
{
}

Zombies::Zombies(sf::RenderWindow &_oknoint, const int  &_zombie_health, sf::Image &_mapImage) {

	int ilosc_x = 1024, ilosc_y = 576;

	for (int k = 0; k < ilosc_y; k++) {
		for (int i = 0; i < ilosc_x; i++) {
			if ((sf::Color::Blue) == _mapImage.getPixel(i, k)) {
				vZombies.push_back(new Zombie(_zombie_health, sf::Vector2f((float)i, (float)k)));

				vZombies.back()->randsmallVelocity(); // losuje predkosc w poziomie
			}
		}
	}
}

Zombies::~Zombies()
{
	for (auto i : vZombies) {
		delete i;
	}
	vZombies.clear();	//std::vector <Zombie*>
}

int Zombies::size()
{
	return vZombies.size();
}

void Zombies::chaseThePlayer(Player & _player, float & frame_time)
{
	for (unsigned int i = 0; i < size(); i++) {

		if ((vZombies[i]->getPosition().x - _player.pos.x < 100) && (vZombies[i]->getPosition().x - _player.pos.x > -100)) {
			if ((vZombies[i]->getPosition().y - _player.pos.y < 100) && (vZombies[i]->getPosition().y - _player.pos.y > -100)) {
				if (vZombies[i]->getPosition().x > _player.pos.x) {
					vZombies[i]->race_to_left(frame_time);
				}
				else
				{
					vZombies[i]->race_to_right(frame_time);
				}
				//is = true;
			}
		}

	}
}

void Zombies::randVelocity(sf::Clock & clock_for_zombies)
{
	//losowanie predkosci i kierunku zombie, co 0.15 sekundy kolejny zombie
	if (clock_for_zombies.getElapsedTime().asMilliseconds() > 150) {
		nr_zombie++;
		if (!(nr_zombie < size())) nr_zombie = 0;
		vZombies[nr_zombie]->randVelocity();
		clock_for_zombies.restart();
	}
}

bool Zombies::zombieBitesPlayer(Player & _player)
{
	for (unsigned int i = 0; i < size(); i++) {

		if ((_player.getGlobalBounds().intersects(vZombies[i]->getGlobalBounds())) && (vZombies[i]->bite == false)) {
			vZombies[i]->bite = true;
			_player.health--;
			std::cout <<"player live points: "<< (int)(_player.health) << std::endl;
			return true;
		}
	}
	return false;
}

void Zombies::moveAndDraw(float & _elapsedTime, const std::vector<sf::RectangleShape>& _vGround, char _tabRed[][576], char _tab[][576], int _nr_of_object[][576], sf::RenderWindow &_okno)
{
	for (unsigned int i = 0; i < size(); i++) {

		//ruch zombie:
		vZombies[i]->move((vZombies[i]->velocity.x) * 1000 * _elapsedTime, (vZombies[i]->velocity.y) * 1000 * _elapsedTime);

		//odbicia od czerwonych scian:
		vZombies[i]->collision_wall(_tabRed);

		//kolizja z podlozem:
		vZombies[i]->collision(_vGround, _tab, _nr_of_object, _elapsedTime);

		//nadanie przyspieszenia od grawitacji:
		if ((vZombies[i]->velocity.y < 1.1*jumpspeed) && (vZombies[i]->intersectsSomething == false))
		{
			vZombies[i]->velocity.y += (gravity * 1000 * _elapsedTime);
		}
		vZombies[i]->intersectsSomething = false;
		_okno.draw(*vZombies[i]);
	}
}
