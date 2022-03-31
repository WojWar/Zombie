#include "Parameters.h"



Parameters::Parameters()
{
}

Parameters::~Parameters()
{
}

Parameters::Parameters(int &player_health, int &zombie_health) {

plik.open("parameters.txt", std::ios::in);

if (plik.good() == true)
{
	///////////////////////////////pierwsza linia - zycie playera
	getline(plik, linia);
	std::cout << "Pierwsza linia z pliku tekstowego: \"" << linia << "\"" << std::endl;
	size_t znalezionaPozycja = linia.find(":");
	if (znalezionaPozycja == std::string::npos) {
		std::cout << "Nie znaleziono znaku ':' w tekscie. Nie wczytano punktow zycia playera." << std::endl;
	}
	else if (linia.at(znalezionaPozycja) == ':') {
		linianr1 = linia.substr(znalezionaPozycja + 1, linia.back());
		player_health = atoi(linianr1.c_str());
		std::cout << "Wczytano punkty zycia playera: " << player_health << std::endl << std::endl; //wyswietlenie linii

	}
	///////////////////////////////druga linia - zycie zombie
	getline(plik, linia);
	std::cout << "Druga linia z pliku tekstowego: \"" << linia << "\"" << std::endl; //wyswietlenie linii
	size_t znalezionaPozycja2 = linia.find(":");
	if (znalezionaPozycja2 == std::string::npos) {
		std::cout << "Nie znaleziono znaku ':' w tekscie. Nie wczytano punktow zycia zombie." << std::endl;
	}
	else if (linia.at(znalezionaPozycja2) == ':') {
		linianr2 = linia.substr(znalezionaPozycja2 + 1, linia.back());
		zombie_health = atoi(linianr2.c_str());
		std::cout << "Wczytano punkty zycia zombie: " << zombie_health << std::endl << std::endl; //wyswietlenie linii
	}
	///////////////////////////////trzecia linia - nazwa pliku z mapa
	getline(plik, linia);
	std::cout << "Trzecia linia z pliku tekstowego: \"" << linia << "\"" << std::endl; //wyswietlenie linii
	size_t znalezionaPozycja3 = linia.find(":");
	if (znalezionaPozycja3 == std::string::npos) {
		std::cout << "Nie znaleziono znaku ':' w tekscie. Nie wczytano nazwy pliku z mapa." << std::endl;
	}
	else if (linia.at(znalezionaPozycja3) == ':') {
		map_name = linia.substr(znalezionaPozycja3 + 1, linia.back());
		//zombie_health = atoi(linianr2.c_str());
		std::cout << "Wczytano plik mapy: " << map_name << std::endl << std::endl; //wyswietlenie linii
	}


	plik.close();
}
	}