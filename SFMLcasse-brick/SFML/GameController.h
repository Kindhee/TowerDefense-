#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include "GameObject.h"
#include "Tour.h"
#include "Projectile.h"
#include "Enemy.h"
#include "LevelCreater.h"
#include "Window.h"
using namespace std;

class GameController
{
public :

	GameController();

	int game();

};

