#pragma once
#include "GameObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Canon
{
public:

	float init_angle;

	float vect_x, vect_y;
	
	Canon();

	void getVect(sf::Shape* shape, sf::RenderWindow* window, sf::Shape* other_shape);

};

