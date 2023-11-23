#include "Enemy.h"

Brick::Brick(int x, int y, int width, int height, const char* img, int health, int reward, float speed) : GameObject(x, y, width, height, img, speed) {

	this->health = health;
	this->reward = reward;
}

Brick::Brick(int x, int y, int width, int height, const char* img, int type) : GameObject(x, y, width, height, img) {

	this->type = type;
}

void Brick::update() {
	health -= 1;
}

bool Brick::mouseOnBrick(float mouse_x, float mouse_y) {
	
	if (type != 1) {
		return false;
	}

	sf::Vector2f position_brick = shape->getPosition();

	if ((isInside(mouse_x, position_brick.x, position_brick.x + width) &&
		isInside(mouse_y, position_brick.y, position_brick.y + height))) {
		return true;
	}
	return false;
}

bool Brick::dropBonus() {
	int chance = random(15);
	if (chance == 1) {
		return true;
	}
	return false;
}