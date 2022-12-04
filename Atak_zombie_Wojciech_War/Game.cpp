#include "Game.h"

Game::Game()
{
	tab = new char*[windowWidth]; //
	nr_of_object = new int*[windowWidth]; //

	for (int i = 0; i < windowWidth; i++)
	{
		tab[i] = new char[windowHeight];
		nr_of_object[i] = new int[windowHeight];
	}

	okno = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Zombie Attack!");

	groundMap2.loadGround();
}

Game::~Game()
{

	for (int i = 0; i < windowWidth; i++)
	{
		delete [] tab[i];
		delete [] nr_of_object[i];
	}

	delete okno;
	delete tab;
	delete nr_of_object;
}

void Game::play()
{


	srand((unsigned int)time(NULL));

	sf::RenderTexture texture;//tekstura z calym podlozem (grunty)
	sf::RenderTexture texture_health_of_player;//tekstura z paskiem zycia

	//Parameters _parametry(player_health, zombie_health);

	Player player(player_health, groundMap2);


	/////////////make tab of keys//////////////
	bool keys[256], keysReleased[256];
	for (int j = 0; j < 256; j++) {
		keys[j] = 0;
	}

	//////////////////////////tworzenie obiektow/////////////////////////////
	objects_to_vector_and_texture(texture, map_name);
	initialize_health_bar(*okno, texture_health_of_player, player);

	//make some zombies
	Zombies _zombies(*okno, zombie_health, _mapImage);
	_zombies.loadTheWalls(_mapImage);

	texture.display();
	texture_health_of_player.display();

	sf::Sprite sprite_health_bar(texture_health_of_player.getTexture());
	sf::Sprite sprite(texture.getTexture());
	sf::Sprite sprite2;

	sprite_health_bar.move(437, 500);
	std::cout << "Pozostalo punktow zycia:" << std::endl;

	okno->setFramerateLimit(30);

	sf::Clock clock;
	sf::Clock clock_for_zombies;
	///////////////////////////////////MAIN LOOP////////////////////////////////
	while (okno->isOpen() && _zombies.areAlive() && player.isAlive())
	{
		//pomiar fps
		float ElapsedTime = clock.getElapsedTime().asSeconds();
		clock.restart();

		sf::Event event;
		while (okno->pollEvent(event)) {
			if (event.type == sf::Event::EventType::KeyPressed) {
				keys[event.key.code] = true;
			}
			else if (event.type == sf::Event::EventType::KeyReleased) {
				keysReleased[event.key.code] = true;
				keys[event.key.code] = false;
			}
			else if (event.type == sf::Event::Closed) {
				okno->close();
			}
		}

		okno->clear(sf::Color::White);
		player.pos.x = player.getPosition().x;
		player.pos.y = player.getPosition().y;
		//sterowanie:

		if (keys[57] && keysReleased[57])
		{
			keysReleased[57] = false;
			bullets.fireBullet(player);
		}

		if (keys[0]) {
			player.velocity.x = -movespeedPlayer;
			player.shooting_direction = false;
		}
		else if (keys[3]) {
			player.velocity.x = movespeedPlayer;
			player.shooting_direction = true;
		}
		else {
			player.velocity.x = 0;
		}
		//if (keys[22] && ((player.intersectsSomething) || ((player.velocity.y > 0.1*jumpspeed) && (player.jumpCounter < 3))) && (keysReleased[22])) {
		//	if (player.intersectsSomething)
		//	{
		//		player.jumpCounter = 0;
		//	}
		//	player.jumpCounter = 0;

		//	keysReleased[22] = false;
		//	player.jumpRequest();
		//	player.intersectsSomething = false;
		//	player.jumpCounter++;
		//}
		if (keys[22] && (keysReleased[22])) {
			keysReleased[22] = false;
			player.jumpRequest();
		}


		//player:		 

		player.performMove(ElapsedTime);



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
		okno->draw(sprite);
		okno->draw(sprite_health_bar);
		okno->draw(player);




		//zombie

		_zombies.randVelocity(clock_for_zombies);

		_zombies.chaseThePlayer(player, ElapsedTime);

		_zombies.moveAndDraw(ElapsedTime, groundRectangles, tab, nr_of_object, *okno);


		bullets.moveAndHit(_zombies, ElapsedTime, *okno, tab);

		okno->display();

	} //while

	////////////////////////////////////Ekrany koncowe:////////////////////////////

	sf::Texture pTexture_you_win;
	sf::Texture pTexture_game_over;

	sf::Sprite pSprite_koniec_gry;

	if (_zombies.areAlive())
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


	okno->draw(pSprite_koniec_gry);
	while (okno->isOpen()) {
		sf::Event event2;
		while (okno->pollEvent(event2)) {
			if (event2.type == sf::Event::Closed) {
				okno->close();
			}
		}

		for (auto i : vectorHealth) {
			delete i;
		}

		vectorHealth.clear();	//std::vector <RectangleShape*>

		bullets.clearMemory();	//std::forward_list <Bullet*>

		groundRectangles.clear();		//std::vector <RectangleShape> 


		okno->draw(pSprite_koniec_gry);
		okno->display();
	}
	//return 0;
}


void Game::objects_to_vector_and_texture(sf::RenderTexture &_textura, std::string &_map_name) {

	std::cout << std::endl << "Trwa ladowanie mapy." << std::endl;

	bool flag = true;
	for (int i = 0; i < windowWidth; i++) {
		for (int j = 0; j < windowHeight; j++) {
			tab[i][j] = 0;
			nr_of_object[i][j] = 0;
		}
	}

	//if (!_mapImage.loadFromFile("map_01.png"))

	if (!_mapImage.loadFromFile(_map_name))
	{
		std::cout << "Error occured during map loading" << std::endl;
		system("pause");
	}
	_textura.create(windowWidth, windowHeight);

	float constant_x_size = 1.0f;
	float constant_y_size = 1.0f;
	float current_x_size;
	float current_y_size;

	sf::RectangleShape shape(sf::Vector2f(1.0f, 1.0f));
	sf::RectangleShape shapeMap(sf::Vector2f(1.0f, 1.0f));
	shape.setFillColor(sf::Color(139, 69, 19));
	shapeMap.setFillColor(sf::Color(50, 50, 19));

	unsigned int temp_i;
	unsigned int temp_k;
	//int add_count = 1;
	for (unsigned int k = 0; k < (unsigned int)windowHeight; k++) {
		for (unsigned int i = 0; i < (unsigned int)windowWidth; i++) {

			shape.setPosition(1.0f*i, 1.0f*k);

			if (((sf::Color::Black) == _mapImage.getPixel(i, k)) && (tab[i][k] == 0)) {
				tab[i][k] = 1;
				nr_of_object[i][k] = (int)(groundRectangles.size());
				current_x_size = 0;
				current_y_size = 0;
				temp_i = i;
				temp_k = k;
				while (((sf::Color::Black) == _mapImage.getPixel(temp_i, k) && (temp_i < (unsigned int)windowWidth - 1) && (tab[temp_i][k] == 0)) || (temp_i == i)) {
					tab[temp_i][k] = 1;
					nr_of_object[temp_i][k] = (int)(groundRectangles.size());
					shape.setSize(sf::Vector2f(current_x_size + constant_x_size, current_y_size));
					current_x_size = current_x_size + constant_x_size;
					temp_i++;
				}

				while (flag && (temp_k < (unsigned int)windowHeight - 1)) {
					flag = true;
					for (unsigned int c = i; c < temp_i; c++) {
						if (((sf::Color::Black) == _mapImage.getPixel(c, temp_k) && (tab[c][temp_k] == 0)) || (temp_k == k)) {
							tab[c][temp_k] = 1;
							nr_of_object[c][temp_k] = (int)(groundRectangles.size());
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
						shape.setSize(sf::Vector2f(current_x_size, current_y_size + constant_y_size));
						current_y_size = current_y_size + constant_y_size;

						//if (temp_k<ilosc_y)
						temp_k++;
					}
				}

				
				//std::cout <<"Ladowanie wiersza: "<< k << std::endl;
				//srand(i);
				//shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
					
				//_textura.draw(shape);
				groundRectangles.push_back(sf::RectangleShape(shape));
				
				i = temp_i;
				flag = true;
			}

		}
	}


	//****************************************************************

	for (unsigned int k = 0; k < (unsigned int)windowHeight-1; k++) {
		for (unsigned int i = 0; i < (unsigned int)windowWidth-1; i++) {


			//if ((sf::Color::Black) == _mapImage.getPixel(i, k)) {

			//	_textura.draw(shapeMap);

			//}
			if (groundMap2.isGround((int)i, (int)k)) {

				shapeMap.setPosition((float)i, (float)k);
				_textura.draw(shapeMap);
				//std::cout << "groundMap.isGround: "  << std::endl;
			}

		}
	}
	//****************************************************************

	std::cout << "Ladowanie mapy zakonczone. Ilosc obiektow podloza: " << groundRectangles.size() << std::endl;


}

void Game::initialize_health_bar(sf::RenderWindow &_okno, sf::RenderTexture &_textura, const Player &_player) {

	_textura.create(150, 15);

	for (int i = 0; i < player_health; i++) {

		vectorHealth.push_back(new sf::RectangleShape());
		vectorHealth.back()->setSize(sf::Vector2f(150 / (float)player_health + 1, 15));
		vectorHealth.back()->setPosition(sf::Vector2f(i * 150 / (float)player_health, 0));
		vectorHealth.back()->setFillColor(sf::Color::Red);

		_textura.draw(*vectorHealth.back());
	}
}



