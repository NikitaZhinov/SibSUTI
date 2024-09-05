module;

#include <SFML/Graphics.hpp>
#include <random>
#include <array>
#include <numbers>
#include <cmath>

import tPointModule;

export module ControlModule;

export template <std::size_t CountPoints>
class Contor {
	struct Point {
		tPoint point;
		double move_angle;
	};

	std::array<Point, CountPoints> points;
	double speed;

	// random generator for random movement
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dis;

	// window size
	int width, height;

public:
	Contor(int width, int height, double speed) : gen(rd()), dis(-3 * speed, 3 * speed), width(width), height(height), speed(speed) {
		double k = std::numbers::pi / (double)CountPoints;
		for (std::size_t i = 0; i < CountPoints / 2; i++)
			points[i].move_angle = k * (double)i;
	}

	void move() {
		for (std::size_t i = 0; i < CountPoints / 2; i++)
			points[i].point.move(std::cos(points[i].move_angle) * speed, std::sin(points[i].move_angle) * speed);

		for (std::size_t i = CountPoints / 2; i < CountPoints; i++)
			points[i].point.move(dis(gen), dis(gen));
	}

	void collision() {
		for (std::size_t i = 0; i < CountPoints / 2; i++) {
			tPoint& cur_point = points[i].point;
			double& cur_angle = points[i].move_angle;

			int left_border = cur_point.getX();
			int right_border = cur_point.getX() + 2. * cur_point.getRadius();
			int top_border = cur_point.getY();
			int bottom_border = cur_point.getY() + 2. * cur_point.getRadius();

			while (cur_angle > 2. * std::numbers::pi)
				cur_angle -= 2. * std::numbers::pi;
			while (cur_angle < 0.)
				cur_angle += 2. * std::numbers::pi;

			if (cur_angle >= 0. && cur_angle < std::numbers::pi / 2.) {
				if (right_border >= width)
					cur_angle = cur_angle + std::numbers::pi - 2. * cur_angle;
				else if (bottom_border >= height)
					cur_angle = cur_angle - 2. * cur_angle;
			}
			else if (cur_angle >= std::numbers::pi / 2. && cur_angle < std::numbers::pi) {
				if (left_border <= 0.)
					cur_angle = std::numbers::pi - cur_angle;
				else if (bottom_border >= height)
					cur_angle = cur_angle + 2. * (std::numbers::pi - cur_angle);
			}
			else if (cur_angle >= std::numbers::pi && cur_angle < 3. * std::numbers::pi / 2.) {
				if (left_border <= 0.)
					cur_angle = cur_angle + std::numbers::pi - 2. * (cur_angle - std::numbers::pi);
				else if (top_border <= 0.)
					cur_angle = cur_angle - 2. * (cur_angle - std::numbers::pi);
			}
			else if (cur_angle >= 3. * std::numbers::pi / 2. && cur_angle < 2. * std::numbers::pi) {
				if (right_border >= width)
					cur_angle = cur_angle - std::numbers::pi + 2. * (2. * std::numbers::pi - cur_angle);
				else if (top_border <= 0.)
					cur_angle = cur_angle + 2. * (2. * std::numbers::pi - cur_angle);
			}
		}

		for (std::size_t i = CountPoints / 2; i < CountPoints; i++) {
			tPoint& cur_point = points[i].point;

			if (cur_point.getX() - cur_point.getRadius() < 0)
				cur_point.move(speed, 0);
			else if (cur_point.getX() + cur_point.getRadius() > width)
				cur_point.move(-speed, 0);

			if (cur_point.getY() - cur_point.getRadius() < 0)
				cur_point.move(0, speed);
			else if (cur_point.getY() + cur_point.getRadius() > height)
				cur_point.move(0, -speed);
		}
	}

	void draw(sf::RenderWindow& window) {
		for (std::size_t i = 0; i < CountPoints; i++)
			points[i].point.draw(window);
	}
};
