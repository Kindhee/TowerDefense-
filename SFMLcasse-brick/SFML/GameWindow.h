#pragma once
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include "GameObject.h"
#include "Canon.h"
#include "Ball.h"
#include "Brick.h"
#include "LevelCreater.h"
#include "Bonus.h"
using namespace std;

class GameWindow
{
public :

	GameWindow();

	int game();

};

