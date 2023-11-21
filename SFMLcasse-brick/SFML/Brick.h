#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
public:

	int health;
	const char* img_bonus = "img/bonus.png";

	Brick(int x, int y, int width, int height, const char* img, int health);

	void init();
	void update();

	bool dropBonus();
};


