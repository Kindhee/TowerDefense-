#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:

	float x, y, width, height, radius;
	float speed, vectX, vectY;
	const char* img;

	sf::Shape* shape;

	GameObject(int x, int y, int width, int height, const char* img);
	GameObject(int x, int y, int size1, int size2);
	GameObject(int x, int y, int radius, const char* img);
	GameObject(int x, int y, int radius);

	int random(int max_number_chance);

	void moveDirection(float time, float vect_x, float vect_y, float speed);

	void setPositionObject(int x, int y);
	void setOriginToCenter();
	void rotate(int degree);
	
	float getMinimumDistance(float distance1, float distance2, float distance3, float distance4);

	bool isInside(float coord, float coord_min, float coord_max);

	bool hasCollided(sf::Shape* other_shape, int other_width, int other_heigth);

	sf::Vector2f newBounceDirection(sf::Shape* other_shape, int other_width, int other_height);

};

