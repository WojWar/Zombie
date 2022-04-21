#include "BgWalls.h"

BgWalls::BgWalls()
{	
	//allocate memory:
	tab_RED = new char*[windowWidth]; //

	for (int i = 0; i < windowWidth; i++)
	{
		tab_RED[i] = new char[windowHeight];
	}
}

void BgWalls::Init(sf::Image &_mapImage)
{


	// start construction:

	std::cout << std::endl << "Trwa ladowanie scian." << std::endl;
	bool flag = true;
	short walls_count = 0;
	for (int i = 0; i < windowWidth; i++) {
		for (int j = 0; j < windowHeight; j++) {
			tab_RED[i][j] = 0;
		}
	}

	float constant_x_size = 1;
	float constant_y_size = 1;
	float current_x_size;
	float current_y_size;

	RectangleShape pix(Vector2f(1, 1));
	pix.setFillColor(Color::Red);

	int temp_i;
	int temp_k;
	//int add_count = 1;
	for (int k = 0; k < windowHeight; k++) {
		for (int i = 0; i < windowWidth; i++) {

			pix.setPosition((float)i, (float)k);
			if (((Color::Red) == _mapImage.getPixel(i, k)) && (tab_RED[i][k] == 0)) {
				tab_RED[i][k] = 1;
				current_x_size = 0;
				current_y_size = 0;
				temp_i = i;
				temp_k = k;
				while (((Color::Red) == _mapImage.getPixel(temp_i, k) && (temp_i < windowWidth - 1) && (tab_RED[temp_i][k] == 0)) || (temp_i == i)) {
					tab_RED[temp_i][k] = 1;
					pix.setSize(Vector2f(current_x_size + constant_x_size, current_y_size));
					current_x_size = current_x_size + constant_x_size;
					temp_i++;
				}

				while (flag && (temp_k < windowHeight - 1)) {
					flag = true;
					for (int c = i; c < temp_i; c++) {
						if (((Color::Red) == _mapImage.getPixel(c, temp_k) && (tab_RED[c][temp_k] == 0)) || (temp_k == k)) {
							tab_RED[c][temp_k] = 1;
						}
						else
						{
							flag = false;
						}
					}
					if (flag == false) {
						for (int c = i; c < temp_i; c++) {
							tab_RED[c][temp_k] = 0;
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
					walls_count++;
				}
				i = temp_i;
				flag = true;
			}

		}
	}

	std::cout << "Ladowanie scian zakonczone. Ilosc obiektow scian: " << walls_count << std::endl << std::endl;

}


BgWalls::~BgWalls()
{
	for (int i = 0; i < windowWidth; i++)
	{
		delete[] tab_RED[i];
	}

	delete tab_RED;
}

char ** BgWalls::getBgWallsTab()
{
	return tab_RED;
}

