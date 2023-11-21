#pragma once
#include "GameObject.h"

class Bonus : public GameObject
{
public:
		float speed_bonus;

		Bonus(int x, int y, int size1, int size2, const char* img);

};


