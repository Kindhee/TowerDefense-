#include "Bonus.h"

Bonus::Bonus(int x, int y, int size1, int size2, const char* img) : GameObject(x, y, size1, size2, img) {
	speed_bonus = 50;
}