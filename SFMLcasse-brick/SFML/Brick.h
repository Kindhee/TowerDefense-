#pragma once
#include "GameObject.h"

class Brick : public GameObject
{
public:

	int health, reward, type;
	const char* img_bonus = "img/bonus.png";

	Brick(int x, int y, int width, int height, const char* img, int health, int reward, float speed);
	Brick(int x, int y, int width, int height, const char* img, int type);

	void init();
	void update();
	bool mouseOnBrick(float mouse_x, float mouse_y);
	bool dropBonus();
};


