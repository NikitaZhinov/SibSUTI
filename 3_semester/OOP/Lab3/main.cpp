#include <SFML/Graphics.hpp>
#include <Windows.h>

import tPointModule;
import ControlModule;

int main() {
	// window size
	int width = 800, height = 800;

	Contor<100> c(width, height, 2.);

	sf::RenderWindow window(sf::VideoMode(width, height), "Lab 3");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		c.move();
		c.collision();
		c.draw(window);

		Sleep(1);

		window.display();
	}

	return 0;
}
