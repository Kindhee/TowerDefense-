#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Canon
{
public:

	float vect_x, vect_y;
	
	Canon();

	void getVect(sf::Shape* shape, sf::Shape* other_shape);

};

