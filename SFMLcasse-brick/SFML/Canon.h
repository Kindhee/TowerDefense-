#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Canon
{
public:

	float init_angle;

	float vect_x, vect_y;
	
	Canon();

	void getVect(sf::Shape* shape, sf::RenderWindow* window, sf::Shape* other_shape);

};

