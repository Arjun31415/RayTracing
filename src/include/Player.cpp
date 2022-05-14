/**
 * @file Player.cpp
 * @author Arjun
 * @brief  Player class with the rays
 * @version 0.1
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "Player.hpp"
#include "debug/debug.hpp"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
inline namespace Object
{
	constexpr const double PI = 3.14159265;
	using Point = Geometry::Point<double>;
	using sf::Vector2f;
	using sf::Vertex;
	using std::pair;
	using std::unique_ptr;
	using std::vector;
	Player::Player()
	{
		x = 0;
		y = 0;
		r = 0;
	}
	Player::Player(double x, double y, double r) : x(x), y(y), r(r) {}
	Player::Player(double x, double y, double r, double w, double h)
		: x(x), y(y), r(r), w(w), h(h)
	{
	}
	void Player::setPosition(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	pair<double, double> Player::getPosition() { return {x, y}; }
	void Player::moveX(double amt)
	{
		if (x + amt + r >= w || x + amt <= r) return;
		x += amt;
	}
	void Player::moveY(double amt)
	{
		if (y + amt + r >= h || y + amt <= r) return;
		y += amt;
	}
	void Player::moveRight() { moveX(DELTA); }
	void Player::moveLeft() { moveX(-DELTA); }
	void Player::moveDown() { moveY(DELTA); }
	void Player::moveUp() { moveY(-DELTA); }
	void Player::draw(sf::RenderWindow &window,
					  const vector<pair<Point, Point>> &lines)
	{
		unique_ptr<sf::CircleShape> p(
			new sf::CircleShape(this->r, POINT_COUNT));
		Vertex origin(Vector2f(this->x, this->y));
		p->setOrigin(this->x, this->y);
		vector<Vertex> end_points;
		for (int i = 0; i <= FOV; i += DTHETA)
		{
			pair<float, float> end_point;
			float x_v = cos(Geometry::deg_to_rad(i));
			float y_v = sin(Geometry::deg_to_rad(i));
			float y1 = this->y, x1 = this->x;

			const Point ray =
				Geometry::cross(Point(0, 0, 1), Point(x_v, y_v, 1));
			for (auto &line : lines)
			{
				auto [p1, p2] = line;
				p1.x -= x1, p1.y = y1 - p1.y, p1.z = 1;
				p2.x -= x1, p2.y = y1 - p2.y, p2.z = 1;

				Point l = Geometry::cross(p1, p2);
				Point Q = Geometry::cross(l, ray);
				if (Q.z == 0) continue;
				Q /= Q.z;
				// if (i == 100)
				// {
				//     debug(line, p1, p2, i);
				//     debug(l, ray, Q, end_point);
				// }
				if (Q.x * x_v >= 0 && Q.y * y_v >= 0)
				{
					int x2 = std::min(p1.x, p2.x), y2 = std::min(p1.y, p2.y),
						x3 = std::max(p1.x, p2.x), y3 = std::max(p1.y, p2.y);
					bool chosen = false;
					if ((int)Q.x >= x2 && (int)Q.x <= x3 && (int)Q.y >= y2 &&
						(int)Q.y <= y3)
						chosen = 1;
					if (chosen)
					{
						end_point = {(Q.x + x1 < EPSILON ? 0 : Q.x + x1),
									 (y1 - Q.y < EPSILON ? 0 : y1 - Q.y)};

						break;
					}
					else continue;
				}
			}
			// debug(end_point);
			end_points.push_back(
				Vertex(Vector2f(end_point.first, end_point.second)));
		}
		for (auto &e : end_points)
		{
			sf::Vertex vertices[] = {origin, e};
			window.draw(vertices, 2, sf::Lines);
		}
		window.draw(*p);
	}
} // namespace Object
