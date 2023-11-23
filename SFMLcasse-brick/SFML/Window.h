#pragma once
#include <SFML/Graphics.hpp>

class Window
{

public :

	sf::RenderWindow* window;
	
	Window();

	void draw(sf::Sprite sprite);

	void draw(sf::Shape* shape);

	void drawText(sf::Text text);

	void display();
};

