#include "Brick.h"

Brick::Brick(int x, int y, int width, int height, const char* img, int health) : GameObject(x, y, width, height, img) {

	this->health = health;
}

void Brick::update() {
	health -= 1;
}

bool Brick::dropBonus() {
	int chance = random(15);
	if (chance == 1) {
		return true;
	}
	return false;
}