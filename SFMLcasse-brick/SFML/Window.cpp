#include "Window.h"

Window::Window() {

	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SFML");

}

void Window::draw(sf::Sprite sprite) {
	window->draw(sprite);
}

void Window::draw(sf::Shape* shape) {
	window->draw(*shape);
}

void Window::drawText(sf::Text text) {
	window->draw(text);
}

void Window::display() {
	window->display();
}
