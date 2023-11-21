#include "GameObject.h"
#include <list>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;


GameObject::GameObject(int x, int y, int width, int height, const char* img) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->img = img;
	speed = 500;
	vectX = 0;
	vectY = 0;
	
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(img)) {
		cout << "failed to load image";
	}

	shape = new sf::RectangleShape(sf::Vector2f(width, height));
	shape->setPosition(x, y);
	shape->setTexture(texture);
}

GameObject::GameObject(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	speed = 500;
	vectX = 0;
	vectY = 0;

	shape = new sf::RectangleShape(sf::Vector2f(width, height));
	shape->setPosition(x, y);
	shape->setFillColor(sf::Color::Red);
}


GameObject::GameObject(int x, int y, int radius, const char* img) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	this->img = img;
	speed = 2000;
	vectX = 0;
	vectY = 0;

	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(img)) {
		cout << "failed to load image";
	}


	shape = new sf::CircleShape(radius);
	shape->setPosition(x, y);
	shape->setTexture(texture);
}


GameObject::GameObject(int x, int y, int radius) {
	this->x = x;
	this->y = y;
	this->radius = radius;
	speed = 500;
	vectX = 0;
	vectY = 0;

	shape = new sf::CircleShape(radius);
	shape->setPosition(x, y);
	shape->setFillColor(sf::Color::Blue);
}

int GameObject::random(int max_number_chance) {
	int randomnumber;
	randomnumber = rand() % max_number_chance;
	return(randomnumber);
}

void GameObject::moveDirection(float time, float vect_x, float vect_y, float speed) {
	x += vect_x * speed * time;
	y += vect_y * speed * time;
	shape->setPosition(x,y);
}

void GameObject::setPositionObject(int x, int y) {
	shape->setPosition(x, y);
}

void GameObject::setOriginToCenter() {
	shape->setOrigin(sf::Vector2f(shape->getLocalBounds().width, shape->getLocalBounds().height) / 2.f);
}

void GameObject::rotate(int degree) {
	shape->rotate(degree);
}

float GameObject::getMinimumDistance(float distance1, float distance2, float distance3, float distance4) {
	float min = distance1;
	list<float> distance_list{distance2, distance3, distance4};
	while(distance_list.empty() == false) {
		if (distance_list.front() < min) {
			min = distance_list.front();
		}
		distance_list.pop_front();
	}
	return min;
}

bool GameObject::isInside(float coord, float coord_min, float coord_max) {
	if (coord > coord_min && coord < coord_max) {
		return true;
	}
	return false;

}

bool GameObject::hasCollided(sf::Shape* other_shape, int other_width, int other_height) {
	sf::Vector2f position_1 = shape->getPosition();
	sf::Vector2f position_2 = other_shape->getPosition();

	if(( isInside(position_1.x, position_2.x, position_2.x + other_width) || 
		isInside(position_1.x + radius * 2, position_2.x, position_2.x + other_width)) &&
		(isInside(position_1.y, position_2.y, position_2.y + other_height) || 
		isInside(position_1.y + radius * 2, position_2.y, position_2.y + other_height))){
		return true;
	} 
	return false;
}


sf::Vector2f GameObject::newBounceDirection(sf::Shape* other_shape, int other_width, int other_height) {
	sf::Vector2f newVect;
	newVect.x = 1;
	newVect.y = 1;

	float top = abs((shape->getPosition().y + radius * 2) - other_shape->getPosition().y);
	float bottom = abs(shape->getPosition().y - (other_shape->getPosition().y + other_height));
	float left = abs((shape->getPosition().x + radius * 2) - other_shape->getPosition().x);
	float right = abs(shape->getPosition().x - (other_shape->getPosition().x + other_width));

	float min_distance = getMinimumDistance(top, bottom, left, right);

	if (min_distance == top or min_distance == bottom) {
		newVect.y = -1;
	}

	if (min_distance == left or min_distance == right) {
		newVect.x = -1;
	}

	return newVect;
}


