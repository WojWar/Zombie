
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>  
#include "Zombie.h"
#include "Player.h"
#include "Bullet.h"
#include <ctime> 
#include <time.h>
#include <fstream> 
#include <stdio.h>
#include <sstream>

using namespace sf;

//podloze i sciany ograniczajace:
std::vector <RectangleShape> vectorRec;
std::vector <RectangleShape> vectorWalls;

//zombiaki i pociski:
std::vector <Zombie*> vectorZombie;
std::list <Bullet*> vectorBullets;

//pasek zycia:
std::vector <RectangleShape*> vectorHealth;

//mapa:
Image _mapImage;

//tablice dla podloża:
char tab[1024][576]; // tutaj wartosc 0 lub 1 czy jest grunt
int nr_of_object[1024][576]; // tutaj nr obiektu w vectorze ktory jest w danym pixelu

//tablice dla scian ograniczajacych:
char tab_RED[1024][576]; // tutaj wartosc 0 lub 1 czy jest sciana
int nr_of_object_RED[1024][576]; // tutaj nr obiektu w vectorze ktory jest w danym pixelu


std::string linianr3; //globalny ciag znakow - nazwa pliku mapy
 
void load_health_from_file(int &player_health,int &zombie_health){
	std::string linia;
	std::fstream plik;
	std::string linianr1;
	std::string linianr2;
	plik.open("parameters.txt", std::ios::in);

	if (plik.good() == true)
	{
			///////////////////////////////pierwsza linia - zycie playera
			getline(plik, linia);
			std::cout <<"Pierwsza linia z pliku tekstowego: \""<< linia <<"\""<< std::endl;  
			size_t znalezionaPozycja = linia.find(":");
			if (znalezionaPozycja == std::string::npos) {
				std::cout << "Nie znaleziono znaku ':' w tekscie. Nie wczytano punktow zycia playera." << std::endl;
			}
			else if (linia.at(znalezionaPozycja)==':') { 
				linianr1 = linia.substr(znalezionaPozycja+1,linia.back());
				player_health= atoi(linianr1.c_str());
				std::cout << "Wczytano punkty zycia playera: " << player_health << std::endl << std::endl; //wyświetlenie linii

			} 
			///////////////////////////////druga linia - zycie zombie
			getline(plik, linia);
			std::cout << "Druga linia z pliku tekstowego: \"" << linia << "\"" << std::endl; //wyświetlenie linii
			size_t znalezionaPozycja2 = linia.find(":");
			if (znalezionaPozycja2 == std::string::npos) {
				std::cout << "Nie znaleziono znaku ':' w tekscie. Nie wczytano punktow zycia zombie." << std::endl;
			}
			else if (linia.at(znalezionaPozycja2) == ':') {
				linianr2 = linia.substr(znalezionaPozycja2 + 1, linia.back());
				zombie_health = atoi(linianr2.c_str());
				std::cout << "Wczytano punkty zycia zombie: " << zombie_health << std::endl << std::endl; //wyświetlenie linii
			}
			///////////////////////////////trzecia linia - nazwa pliku z mapa
			getline(plik, linia);
			std::cout << "Trzecia linia z pliku tekstowego: \"" << linia << "\"" << std::endl; //wyświetlenie linii
			size_t znalezionaPozycja3 = linia.find(":");
			if (znalezionaPozycja3 == std::string::npos) {
				std::cout << "Nie znaleziono znaku ':' w tekscie. Nie wczytano nazwy pliku z mapa." << std::endl;
			}
			else if (linia.at(znalezionaPozycja3) == ':') {
				linianr3 = linia.substr(znalezionaPozycja3 + 1, linia.back());
				//zombie_health = atoi(linianr2.c_str());
				std::cout << "Wczytano plik mapy: " << linianr3 << std::endl << std::endl; //wyświetlenie linii
			}

		
		plik.close();
	}
}

void makeSomeZombies(RenderWindow &_oknoint,int  &_zombie_health) {

	int ilosc_x = 1024, ilosc_y = 576;

	for (int k = 0; k < ilosc_y; k++) {
		for (int i = 0; i < ilosc_x; i++) {
			if ((Color::Blue) == _mapImage.getPixel(i, k)){
				vectorZombie.push_back(new Zombie(_zombie_health));
				vectorZombie.back()->setPosition(Vector2f(i, k));
				vectorZombie.back()->velocity.y = 0;
				vectorZombie.back()->velocity.x = 0;
				vectorZombie.back()->randsmallVelocity(); // losuje predkosc w poziomie
			}
		}
	}
}
 
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

	double constant_x_size = 1;
	double constant_y_size = 1;
	double current_x_size = constant_x_size;
	double current_y_size = constant_y_size;

	RectangleShape pix(Vector2f(1, 1));
	pix.setFillColor(Color::Red);

	int temp_i = 0;
	int temp_k = 0;
	//int add_count = 1;
	for (int k = 0; k < ilosc_y; k++) {
		for (int i = 0; i < ilosc_x; i++) {

			pix.setPosition(i, k);
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

						if (temp_k<ilosc_y)
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

void objects_to_vector_and_texture(sf::RenderTexture &_textura) {

	std::cout << std::endl << "Trwa ladowanie mapy." << std::endl;

	bool flag = true;
	for (int i = 0; i < 1024; i++) {
		for (int j = 0; j < 576; j++) {
			tab[i][j] = 0;
			nr_of_object[i][j] = 0;
		}
	}

	//if (!_mapImage.loadFromFile("map_01.png"))

	if (!_mapImage.loadFromFile(linianr3))
	{
		std::cout << "BLAD" << std::endl;
		system("pause");
	}
	int ilosc_x = 1024, ilosc_y = 576;
	_textura.create(1024, 576);

	double constant_x_size = _textura.getSize().x / ilosc_x;
	double constant_y_size = _textura.getSize().y / ilosc_y;
	double current_x_size = constant_x_size;
	double current_y_size = constant_y_size;

	RectangleShape shape(Vector2f(_textura.getSize().x / ilosc_x, _textura.getSize().y / ilosc_y));
	shape.setFillColor(Color(139, 69, 19));

	int temp_i = 0;
	int temp_k = 0;
	//int add_count = 1;
	for (int k = 0; k < ilosc_y; k++) {
		for (int i = 0; i < ilosc_x; i++) {

			shape.setPosition(_textura.getSize().x*i / ilosc_x, _textura.getSize().y*k / ilosc_y);
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
					for (int c = i; c < temp_i; c++) {
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
						for (int c = i; c < temp_i; c++) {
							tab[c][temp_k] = 0;
							nr_of_object[c][temp_k] = 0;
						}
					}

					if (flag == true) {
						shape.setSize(Vector2f(current_x_size, current_y_size + constant_y_size));
						current_y_size = current_y_size + constant_y_size;

						if (temp_k<ilosc_y)
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

void initialize_health_bar(RenderWindow &_okno, sf::RenderTexture &_textura,Player &_player){

	_textura.create(150, 15); 
	int full_health = _player.health;
  
	for (int i = 0; i <full_health; i++) {

			vectorHealth.push_back(new RectangleShape());
			vectorHealth.back()->setSize(sf::Vector2f(150/ full_health+1, 15));
			vectorHealth.back()->setPosition(Vector2f(i*150/ full_health, 0));
			vectorHealth.back()->setFillColor(Color::Red);

			_textura.draw(*vectorHealth.back());
	} 
}


int main()
{
	RenderWindow okno(sf::VideoMode(1024, 576), "Atak Zombiaków");

	sf::Clock clock;
	sf::Clock clock_for_zombies;

	//licznik - zombie, ktorego predkosc jest losowana:
	int nr_zombie = 0;
	//licznik - zombie, ktorego obslugiwane jest przesuniecie, kolizja, grawitacja, rysowanie:
	int nr_mov = 0;
	//
	int bullet_to_erase; //nr pocisku w wektorze do skasowania
	srand((unsigned int)time(NULL));

	sf::RenderTexture texture;//tekstura z całym podłożem (grunty)
	sf::RenderTexture texture_walls_for_zombies;//tekstura z scianami
	sf::RenderTexture texture_health_of_player;//tekstura z paskiem zycia


	const float gravity = 0.001; 
	int zombie_health=5;
	int player_health=15;
	float movespeed = 0.1f, jumpspeed = 0.4f;

	load_health_from_file(player_health, zombie_health);

	Player player(player_health);

	/////////////make tab of keys//////////////
	bool keys[256], upReleased = true, upN = true;
	for (int j = 0; j < 256; j++) {
		keys[j] = 0;
	}


	//////////////////////////tworzenie obiektów/////////////////////////////
	objects_to_vector_and_texture(texture);
	walls_for_zombies(texture_walls_for_zombies);  
	initialize_health_bar(okno, texture_health_of_player,player);
	makeSomeZombies(okno,zombie_health);
	 
	
	texture_walls_for_zombies.display();
	texture.display();
	texture_health_of_player.display();

	sf::Sprite sprite_health_bar(texture_health_of_player.getTexture());
	sf::Sprite sprite(texture.getTexture());
	sf::Sprite sprite2(texture_walls_for_zombies.getTexture());

	sprite_health_bar.move(437,500);
	std::cout << "Pozostalo punktow zycia:" << std::endl;

	okno.setFramerateLimit(90);
	///////////////////////////////////MAIN LOOP////////////////////////////////
	while (okno.isOpen() && vectorZombie.size() && player.health)
	{
		//pomiar fps
		float ElapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				okno.close();
			}
			else if (event.type == sf::Event::EventType::KeyPressed) {
				for (int i = 'a'; i < 'z'; i++) {
					if (event.key.code + 97 == i) {
						keys[i] = true;
					}
				}
			}
			else if (event.type == sf::Event::EventType::KeyReleased) {
				for (int i = 'a'; i < 'z'; i++) {
					if (event.key.code + 97 == i) {
						keys[i] = false;
					}
					if (event.key.code + 97 == 'w') {
						upReleased = true;
					}
					if (event.key.code + 97 == 'n') {
						upN = true;
					}
				}
			}
		}

		okno.clear(sf::Color::White);
		player.position.x = player.getPosition().x;
		player.position.y = player.getPosition().y;
		//sterowanie:
		if (keys['g'] && upN)
		{
			std::cout << vectorZombie.size() << std::endl;
		} 
		if (keys['n'] && upN)
		{
			upN = false;
			vectorBullets.push_back(new Bullet(player));
		}

		if (keys['a']) {
			player.velocity.x = -movespeed;
			player.shooting_direction = false;
		}
		else if (keys['d']) {
			player.velocity.x = movespeed ;
			player.shooting_direction = true;
		}
		else {
			player.velocity.x = 0;
		}
		if (keys['w'] && ((player.intersectsSomething) || ((player.velocity.y > 0.1*jumpspeed) && (player.jumpCounter < 3))) && (upReleased)) {
			if (player.intersectsSomething)
			{
				player.jumpCounter = 0;
			}
			upReleased = false;
			player.velocity.y = -jumpspeed;// *1000 * ElapsedTime;
			player.intersectsSomething = false;
			player.jumpCounter++;
		}


		//player:		 

		player.move(player.velocity.x * 1000 * ElapsedTime, player.velocity.y * 1000 * ElapsedTime);
		player.gravity_acceleration(gravity * 1000 * ElapsedTime, jumpspeed);// ElapsedTime);
		player.collision(vectorRec, tab, nr_of_object, ElapsedTime);

		player.are_close(vectorZombie, ElapsedTime);

		if (player.zombie_bites_player(vectorZombie))
		{
			//odjecie punktu zycia na pasku zycia:

			texture_health_of_player.clear(sf::Color::White);
			vectorHealth.pop_back();
			for (int i = 0; i < vectorHealth.size(); i++)
			{
				texture_health_of_player.draw(*vectorHealth[i]);
			}
			texture_health_of_player.display();
		}


		//draw textures:
		okno.draw(sprite);
		okno.draw(sprite_health_bar);
		okno.draw(player);


		//losowanie predkosci i kierunku zombie, co 0.15 sekundy kolejny zombie
		if (clock_for_zombies.getElapsedTime().asMilliseconds() > 150) {
			
			nr_zombie++;
			if (!(nr_zombie < vectorZombie.size())) nr_zombie = 0;

			vectorZombie[nr_zombie]->randVelocity();
			clock_for_zombies.restart();
		}

		

		//zombie
		for (int i = 0; i < vectorZombie.size(); i++) {

			//ruch zombie:
			vectorZombie[i]->move((vectorZombie[i]->velocity.x) * 1000 * ElapsedTime, (vectorZombie[i]->velocity.y) * 1000 * ElapsedTime);


			//odbicia od czerwonych scian:
			vectorZombie[i]->collision_wall(tab_RED);

			//kolizja z podlozem:
			vectorZombie[i]->collision(vectorRec, tab, nr_of_object, ElapsedTime);

			//nadanie przyspieszenia od grawitacji:
			if ((vectorZombie[i]->velocity.y < 1.1*jumpspeed) && (vectorZombie[i]->intersectsSomething == false))
			{
				vectorZombie[i]->velocity.y += (gravity * 1000 * ElapsedTime);
			}
			vectorZombie[i]->intersectsSomething = false;
			okno.draw(*vectorZombie[i]);
		}

		//for (T &i : l)
		//std::list <Bullet*> vectorBullets;
		 
		//pociski    
		if (!vectorBullets.empty()) {
//			for (int i = 0; i < vectorBullets.size(); i++) {
			for (std::list<Bullet*>::iterator vB_it = vectorBullets.begin(); vB_it != vectorBullets.end();) {
				if (vB_it != vectorBullets.end()) {

					//ruch pociskow:
					(*vB_it)->move(((*vB_it)->velocity.x) * 1000 * ElapsedTime, ((*vB_it)->velocity.y) * 1000 * ElapsedTime);

					okno.draw((**vB_it));

					//usuwanie pociskow po zderzeniu
					if (((*vB_it)->is_wall(tab)) || ((*vB_it)->is_zombie(vectorZombie)))
					{
						if (vB_it != vectorBullets.end()) {
							vectorBullets.erase(vB_it++);
						}
					}
					else {
						++vB_it;
					}
				}
				
			}
		}
		
		okno.display(); 
		
	} //while

	////////////////////////////////////Ekrany koncowe:////////////////////////////

	sf::Texture pTexture_you_win;
	sf::Texture pTexture_game_over;

	sf::Sprite pSprite_koniec_gry;

	if (vectorZombie.size()) 
	{
		if (!pTexture_game_over.loadFromFile("game_over.png"))
		{
			std::cout << "BLAD" << std::endl;
			system("pause");
		}
		pSprite_koniec_gry.setTexture(pTexture_game_over);
	}
	else
	{
		if (!pTexture_you_win.loadFromFile("koniec_gry.png"))
		{
			std::cout << "BLAD" << std::endl;
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

		okno.draw(pSprite_koniec_gry);
		okno.display();
	}
	return 0;
}
