#pragma once
#include "Brick.h"
#include <vector>
#include <fstream>
using namespace std;

class LevelCreater
{
public:

	const char* img_brick_blue;
	const char* img_brick_red;
	const char* img_brick_yellow;


	LevelCreater();

	vector<Brick*> loadTable(int level);

};