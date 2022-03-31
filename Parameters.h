#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

class Parameters
{
public:
	Parameters();
	Parameters(int &player_health, int &zombie_health);

	~Parameters();

	std::string linia;
	std::fstream plik;
	std::string linianr1;
	std::string linianr2;
	std::string map_name;//map


};

