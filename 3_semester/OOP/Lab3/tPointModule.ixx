module;

#include <random>
#include <SFML/Graphics.hpp>

export module tPointModule;

export class tPoint {
	double x, y;
	unsigned char color[3];
	double radius;

	sf::CircleShape share;

public:
	tPoint() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 255);

		setRadius(10);
		setPos(getRadius(), getRadius());
		setColor(dis(gen), dis(gen), dis(gen));
	}

	tPoint(double x, double y) : tPoint() {
		setPos(x, y);
	}

	tPoint(double x, double y, unsigned char r, unsigned char g, unsigned char b) : tPoint() {
		setPos(x, y);
		setColor(r, g, b);
	}

	double getX() {
		return x;
	}

	double getY() {
		return y;
	}

	unsigned char* getColor() {
		return color;
	}

	double getRadius() {
		return radius;
	}

	void setX(double x) {
		setPos(x, y);
	}

	void setY(double y) {
		setPos(x, y);
	}

	void setPos(double x, double y) {
		this->x = x;
		this->y = y;
		share.setPosition(sf::Vector2f(x, y));
	}

	void setColor(unsigned char r, unsigned char g, unsigned char b) {
		this->color[0] = r;
		this->color[1] = g;
		this->color[2] = b;
		share.setFillColor(sf::Color(color[0], color[1], color[2]));
	}

	void setRadius(double radius) {
		this->radius = radius;
		share.setRadius(radius);
	}

	void move(double x, double y) {
		setPos(this->x + x, this->y + y);
	}

	void draw(sf::RenderWindow& window) {
		window.draw(share);
	}
};
