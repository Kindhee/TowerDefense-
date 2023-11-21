#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:

	Ball(int x, int y, int size1, const char* img);

	bool windowCollided(sf::RenderWindow* window);

	float invertDirection(float speed);

};

