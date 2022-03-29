
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <cmath>  
#include "Zombies.h"
#include "Player.h"
#include "Bullet.h"
#include "Parameters.h"
#include "Globals.h"
#include <ctime> 
#include <time.h>
#include <fstream> 
#include <stdio.h>
#include <sstream>

using namespace sf;



//podloze i sciany ograniczajace:
std::vector <RectangleShape> vectorRec;
std::vector <RectangleShape> vectorWalls;

std::forward_list <Bullet*> vectorBullets;

//pasek zycia:
std::vector <RectangleShape*> vectorHealth;

//mapa:
Image _mapImage;

//tablice dla podloza:
char tab[1024][576]; // tutaj wartosc 0 lub 1 czy jest grunt
int nr_of_object[1024][576]; // tutaj nr obiektu w vectorze ktory jest w danym pixelu

//tablice dla scian ograniczajacych:
char tab_RED[1024][576]; // tutaj wartosc 0 lub 1 czy jest sciana
int nr_of_object_RED[1024][576]; // tutaj nr obiektu w vectorze ktory jest w danym pixelu


 
void walls_for_zombies(RenderTexture &_texture) {
	std::cout << std::endl << "Trwa ladowanie scian." << std::endl;
	bool flag = true;
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 576; j++) {
			tab_RED[i][j] = 0;
			nr_of_object_RED[i][j] = 0;
		}
	}

	 
	int ilosc_x = 1024, ilosc_y = 576;

	_texture.create(1024, 576);

	float constant_x_size = 1;
	float constant_y_size = 1;
	float current_x_size;
	float current_y_size;

	RectangleShape pix(Vector2f(1, 1));
	pix.setFillColor(Color::Red);

	int temp_i;
	int temp_k;
	//int add_count = 1;
	for (int k = 0; k < ilosc_y; k++) {
		for (int i = 0; i < ilosc_x; i++) {

			pix.setPosition((float)i, (float)k);
			if (((Color::Red) == _mapImage.getPixel(i, k)) && (tab_RED[i][k] == 0)) {
				tab_RED[i][k] = 1;
				nr_of_object_RED[i][k] = (int)(vectorWalls.size());
				current_x_size = 0;
				current_y_size = 0;
				temp_i = i;
				temp_k = k;
				while (((Color::Red) == _mapImage.getPixel(temp_i, k) && (temp_i<ilosc_x - 1) && (tab_RED[temp_i][k] == 0)) || (temp_i == i)) {
					tab_RED[temp_i][k] = 1;
					nr_of_object_RED[temp_i][k] = (int)(vectorWalls.size());
					pix.setSize(Vector2f(current_x_size + constant_x_size, current_y_size));
					current_x_size = current_x_size + constant_x_size;
					temp_i++;
				}

				while (flag && (temp_k<ilosc_y - 1)) {
					flag = true;
					for (int c = i; c < temp_i; c++) {
						if (((Color::Red) == _mapImage.getPixel(c, temp_k) && (tab_RED[c][temp_k] == 0)) || (temp_k == k)) {
							tab_RED[c][temp_k] = 1;
							nr_of_object_RED[c][temp_k] = (int)(vectorWalls.size());
						}
						else
						{
							flag = false;
						}
					}
					if (flag == false) {
						for (int c = i; c < temp_i; c++) {
							tab_RED[c][temp_k] = 0;
							nr_of_object_RED[c][temp_k] = 0;
						}
					}

					if (flag == true) {
						pix.setSize(Vector2f(current_x_size, current_y_size + constant_y_size));
						current_y_size = current_y_size + constant_y_size;

						//if (temp_k<ilosc_y)
							temp_k++;
					}
				}
				{
					_texture.draw(pix);
					vectorWalls.push_back(pix);
				}
				i = temp_i;
				flag = true;
			}

		}
	}

	std::cout<<"Ladowanie scian zakonczone. Ilosc obiektow scian: " << vectorWalls.size() << std::endl << std::endl;
	 
}

void objects_to_vector_and_texture(sf::RenderTexture &_textura, std::string _map_name) {

	std::cout << std::endl << "Trwa ladowanie mapy." << std::endl;

	bool flag = true;
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 576; j++) {
			tab[i][j] = 0;
			nr_of_object[i][j] = 0;
		}
	}

	//if (!_mapImage.loadFromFile("map_01.png"))

	if (!_mapImage.loadFromFile(_map_name))
	{
		std::cout << "BLAD" << std::endl;
		system("pause");
	}
	unsigned int ilosc_x = 1024, ilosc_y = 576;
	_textura.create(1024, 576);

	float constant_x_size = _textura.getSize().x / (float)ilosc_x;
	float constant_y_size = _textura.getSize().y / (float)ilosc_y;
	float current_x_size;
	float current_y_size;

	RectangleShape shape(Vector2f((float)_textura.getSize().x / ilosc_x, (float)_textura.getSize().y / ilosc_y));
	shape.setFillColor(Color(139, 69, 19));

	unsigned int temp_i;
	unsigned int temp_k;
	//int add_count = 1;
	for (unsigned int k = 0; k < ilosc_y; k++) {
		for (unsigned int i = 0; i < ilosc_x; i++) {

			shape.setPosition((float)_textura.getSize().x*i / ilosc_x, (float)_textura.getSize().y*k / ilosc_y);
			if (((Color::Black) == _mapImage.getPixel(i, k)) && (tab[i][k] == 0)) {
				tab[i][k] = 1;
				nr_of_object[i][k] = (int)(vectorRec.size());
				current_x_size = 0;
				current_y_size = 0;
				temp_i = i;
				temp_k = k;
				while (((Color::Black) == _mapImage.getPixel(temp_i, k) && (temp_i<ilosc_x - 1) && (tab[temp_i][k] == 0)) || (temp_i == i)) {
					tab[temp_i][k] = 1;
					nr_of_object[temp_i][k] = (int)(vectorRec.size());
					shape.setSize(Vector2f(current_x_size + constant_x_size, current_y_size));
					current_x_size = current_x_size + constant_x_size;
					temp_i++;
				}

				while (flag && (temp_k<ilosc_y - 1)) {
					flag = true;
					for (unsigned int c = i; c < temp_i; c++) {
						if (((Color::Black) == _mapImage.getPixel(c, temp_k) && (tab[c][temp_k] == 0)) || (temp_k == k)) {
							tab[c][temp_k] = 1;
							nr_of_object[c][temp_k] = (int)(vectorRec.size());
						}
						else
						{
							flag = false;
						}
					}
					if (flag == false) {
						for (unsigned int c = i; c < temp_i; c++) {
							tab[c][temp_k] = 0;
							nr_of_object[c][temp_k] = 0;
						}
					}

					if (flag == true) {
						shape.setSize(Vector2f(current_x_size, current_y_size + constant_y_size));
						current_y_size = current_y_size + constant_y_size;

						//if (temp_k<ilosc_y)
							temp_k++;
					}
				}

				{
					//std::cout <<"Ladowanie wiersza: "<< k << std::endl;
					_textura.draw(shape);
					vectorRec.push_back(shape);
				}
				i = temp_i;
				flag = true;
			}

		}
	}


	std::cout << "Ladowanie mapy zakonczone. Ilosc obiektow podloza: "<<vectorRec.size()<<  std::endl;
	 

}

void initialize_health_bar(RenderWindow &_okno, sf::RenderTexture &_textura,const Player &_player){

	_textura.create(150, 15); 
	char full_health = _player.health;
  
	for (int i = 0; i <full_health; i++) {

			vectorHealth.push_back(new RectangleShape());
			vectorHealth.back()->setSize(sf::Vector2f(150/ (float)full_health+1, 15));
			vectorHealth.back()->setPosition(Vector2f(i*150/ (float)full_health, 0));
			vectorHealth.back()->setFillColor(Color::Red);

			_textura.draw(*vectorHealth.back());
	} 
}

int main()
{
	RenderWindow okno(sf::VideoMode(1024, 576), "Zombie Attack!");

	sf::Clock clock;
	sf::Clock clock_for_zombies;

	srand((unsigned int)time(NULL));

	sf::RenderTexture texture;//tekstura z calym podlozem (grunty)
	sf::RenderTexture texture_walls_for_zombies;//tekstura z scianami
	sf::RenderTexture texture_health_of_player;//tekstura z paskiem zycia

	Parameters _parametry(player_health, zombie_health);

	Player player(player_health);


	/////////////make tab of keys//////////////
	bool keys[256], keysReleased[256];
	for (int j = 0; j < 256; j++) {
		keys[j] = 0;
	}

	//////////////////////////tworzenie obiektow/////////////////////////////
	objects_to_vector_and_texture(texture, _parametry.map_name);
	walls_for_zombies(texture_walls_for_zombies);  
	initialize_health_bar(okno, texture_health_of_player,player);

	//make some zombies

	Zombies _zombies(okno, zombie_health, _mapImage);
	 
	
	texture_walls_for_zombies.display();
	texture.display();
	texture_health_of_player.display();

	sf::Sprite sprite_health_bar(texture_health_of_player.getTexture());
	sf::Sprite sprite(texture.getTexture());
	sf::Sprite sprite2;

	sprite_health_bar.move(437,500);
	std::cout << "Pozostalo punktow zycia:" << std::endl;

	okno.setFramerateLimit(30);
	///////////////////////////////////MAIN LOOP////////////////////////////////
	while (okno.isOpen() && _zombies.size() && player.health)
	{
		//pomiar fps
		float ElapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed) {
				keys[event.key.code] = true;
			}
			else if (event.type == sf::Event::EventType::KeyReleased) {
				keysReleased[event.key.code] = true;
				keys[event.key.code] = false;
			}
			else if (event.type == sf::Event::Closed) {
				okno.close();
			}
		}

		okno.clear(sf::Color::White);
		player.pos.x = player.getPosition().x;
		player.pos.y = player.getPosition().y;
		//sterowanie:

		if (keys[57] && keysReleased[57])
		{
			keysReleased[57] = false;
			//vectorBullets.push(new Bullet(player));
 			vectorBullets.push_front(new Bullet(player));
		}

		if (keys[0]) {
			player.velocity.x = -movespeed;
			player.shooting_direction = false;
		}
		else if (keys[3]) {
			player.velocity.x = movespeed ;
			player.shooting_direction = true;
		}
		else {
			player.velocity.x = 0;
		}
		if (keys[22] && ((player.intersectsSomething) || ((player.velocity.y > 0.1*jumpspeed) && (player.jumpCounter < 3))) && (keysReleased[22])) {
			if (player.intersectsSomething)
			{
				player.jumpCounter = 0;
			}
			keysReleased[22] = false;
			player.velocity.y = -jumpspeed;// *1000 * ElapsedTime;
			player.intersectsSomething = false;
			player.jumpCounter++;
		}


		//player:		 

		player.move(player.velocity.x * 1000 * ElapsedTime, player.velocity.y * 1000 * ElapsedTime);
		player.collision(vectorRec, tab, nr_of_object, ElapsedTime);
		player.gravity_acceleration(gravity * 1000 * ElapsedTime, jumpspeed);// ElapsedTime);



		if (_zombies.zombieBitesPlayer(player))
		{
			//odjecie punktu zycia na pasku zycia:

			texture_health_of_player.clear(sf::Color::White);

			delete vectorHealth.back();
			vectorHealth.pop_back();

			for (unsigned int i = 0; i < vectorHealth.size(); i++)
			{
				texture_health_of_player.draw(*vectorHealth[i]);
			}
			texture_health_of_player.display();
		}


		//draw textures:
		okno.draw(sprite);
		okno.draw(sprite_health_bar);
		okno.draw(player);




		//zombie

		_zombies.randVelocity(clock_for_zombies);

		_zombies.chaseThePlayer(player, ElapsedTime);

		_zombies.moveAndDraw(ElapsedTime, vectorRec, tab_RED, tab, nr_of_object, okno);

		//pociski    
		if (!vectorBullets.empty()) {
			int i = 0;
			for (auto vB_it : vectorBullets)
			{
				if (((*vB_it).is_wall(tab)) || ((*vB_it).is_zombie(_zombies.vZombies)))
				{
					delete vB_it;
					vectorBullets.remove(vB_it);
					break;
				}
				else
				{
					(*vB_it).move(((*vB_it).velocity.x) * 1000 * ElapsedTime, ((*vB_it).velocity.y) * 1000 * ElapsedTime);
					okno.draw((*vB_it));
				}
				i++;
			}

			std::cout << "vectorBullets: " << i << std::endl;
		}
		
		okno.display(); 
		
	} //while

	////////////////////////////////////Ekrany koncowe:////////////////////////////

	sf::Texture pTexture_you_win;
	sf::Texture pTexture_game_over;

	sf::Sprite pSprite_koniec_gry;

	if (_zombies.size()) 
	{
		if (!pTexture_game_over.loadFromFile("game_over.png"))
		{
			std::cout << "Game over!" << std::endl;
			std::cout << "cant load from file: game_over.png" << std::endl;
			system("pause");
		}
		pSprite_koniec_gry.setTexture(pTexture_game_over);
	}
	else
	{
		if (!pTexture_you_win.loadFromFile("koniec_gry.png"))
		{
			std::cout << "You Win!" << std::endl;
			std::cout << "cant load from file: koniec_gry.png" << std::endl;
			system("pause");
		}
		pSprite_koniec_gry.setTexture(pTexture_you_win);
	}
	

	okno.draw(pSprite_koniec_gry);
	while (okno.isOpen()) {
		Event event2;
		while (okno.pollEvent(event2)) {
			if (event2.type == sf::Event::Closed) {
				okno.close();
			}
		}

		for (auto i : vectorHealth) {
			delete i;
		}
		for (auto i : vectorBullets) {
			delete i;
		}

		vectorHealth.clear();	//std::vector <RectangleShape*>

		vectorBullets.clear();	//std::forward_list <Bullet*>

		vectorRec.clear();		//std::vector <RectangleShape> 
		vectorWalls.clear();	//std::vector <RectangleShape>


		okno.draw(pSprite_koniec_gry);
		okno.display();
	}
	return 0;
}
