#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

bool Map::isGround(int x, int y)
{
	return false;
}

void Map::initialise(sf::RenderTexture &_textura, std::string &_map_name) {

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

	float constant_x_size = _textura.getSize().x / (float)windowWidth;//windowWidth
	float constant_y_size = _textura.getSize().y / (float)windowHeight;//windowHeight
	float current_x_size;
	float current_y_size;

	sf::RectangleShape shape(sf::Vector2f((float)_textura.getSize().x / windowWidth, (float)_textura.getSize().y / windowHeight));
	shape.setFillColor(sf::Color(139, 69, 19));

	unsigned int temp_i;
	unsigned int temp_k;
	//int add_count = 1;
	for (unsigned int k = 0; k < windowHeight; k++) {
		for (unsigned int i = 0; i < windowWidth; i++) {

			shape.setPosition((float)_textura.getSize().x*i / windowWidth, (float)_textura.getSize().y*k / windowHeight);
			if (((sf::Color::Black) == _mapImage.getPixel(i, k)) && (tab[i][k] == 0)) {
				tab[i][k] = 1;
				nr_of_object[i][k] = (int)(groundRectangles.size());
				current_x_size = 0;
				current_y_size = 0;
				temp_i = i;
				temp_k = k;
				while (((sf::Color::Black) == _mapImage.getPixel(temp_i, k) && (temp_i < windowWidth - 1) && (tab[temp_i][k] == 0)) || (temp_i == i)) {
					tab[temp_i][k] = 1;
					nr_of_object[temp_i][k] = (int)(groundRectangles.size());
					shape.setSize(sf::Vector2f(current_x_size + constant_x_size, current_y_size));
					current_x_size = current_x_size + constant_x_size;
					temp_i++;
				}

				while (flag && (temp_k < windowHeight - 1)) {
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

				{
					//std::cout <<"Ladowanie wiersza: "<< k << std::endl;
					_textura.draw(shape);
					groundRectangles.push_back(shape);
				}
				i = temp_i;
				flag = true;
			}

		}
	}


	std::cout << "Ladowanie mapy zakonczone. Ilosc obiektow podloza: " << groundRectangles.size() << std::endl;


}
