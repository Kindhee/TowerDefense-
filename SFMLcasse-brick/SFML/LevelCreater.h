#pragma once
#include "Brick.h"
#include <vector>
#include <fstream>
using namespace std;

class LevelCreater
{
public:

	const char* ennemy_one;
	const char* ennemy_two;
	const char* ennemy_three;
	const char* tile_one;
	const char* tile_two;
	const char* tile_three;

	LevelCreater();

	vector<Brick*> loadTable(int level);
	vector<Brick*> loadGrid(int level);

};