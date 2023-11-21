#include "Ball.h"

Ball::Ball(int x, int y, int size1, const char* img) : GameObject(x, y, size1, img) {

}


bool Ball::windowCollided(sf::RenderWindow* window) {
	sf::Vector2f position_1 = shape->getPosition();
	if (position_1.y < 0 || window->getSize().x < (position_1.x + radius * 2) || position_1.x < 0 || window->getSize().y < position_1.y + radius) {
		return true;
	} 
	return false;
}

float Ball::invertDirection(float speed) {
	return speed = -speed;
}
