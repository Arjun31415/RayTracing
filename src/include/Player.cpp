/**
 * @file Player.cpp
 * @author Arjun
 * @brief  Player class with the rays
 * @version 0.1
 * @date 2022-05-13
 *
 */
#include "Physics/Geometry.hpp"
#include "Player.hpp"
#include "debug/debug.hpp"
#include <SFML/Graphics/Color.hpp>
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
	Player::Player() : x(0), y(0), r(0) {}
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
		// the light source
		unique_ptr<sf::CircleShape> p(
			new sf::CircleShape(this->r, POINT_COUNT));
		vector<Vertex> end_points;
		float y1 = this->y, x1 = this->x;
		auto cmp = [](const Point &a, const Point &b)
		{ return dot(a, a) < dot(b, b); };
		for (double i = turn; i <= turn + FOV; i += DTHETA)
		{
			Point end_point(this->w + 1, this->h + 1, 100);
			float *x_v = new float(cos(Geometry::deg_to_rad(i)));
			float *y_v = new float(sin(Geometry::deg_to_rad(i)));
			const Point ray_dir = Point(*x_v, *y_v);
			delete x_v;
			delete y_v;
			for (auto &line : lines)
			{
				auto [p1, p2] = line;
				p1.x -= x1, p1.y = y1 - p1.y, p1.z = 0;
				p2.x -= x1, p2.y = y1 - p2.y, p2.z = 0;
				Point intx;
				int *temp = new int(Geometry::ray_intersection(
					Point(0, 0, 0), ray_dir, p1, p2, intx));
				if (*temp == 1)
				{
					end_point = std::min(intx, end_point, cmp);
				}
				delete temp;
			}
			end_point.x += x1, end_point.y = y1 - end_point.y;
			end_points.push_back(
				Vertex(Vector2f(end_point.x, end_point.y), sf::Color::Red));
		}
		Vertex origin(Vector2f(this->x, this->y), sf::Color::Red);
		for (auto &e : end_points)
		{
			sf::Vertex vertices[] = {origin, e};
			window.draw(vertices, 2, sf::Lines);
			/* window.draw(&e, 1, sf::Points); */
		}
		// Uncomment the following to see the generated lines
		/* for (auto &line : lines) */
		/* { */
		/* 	sf::Vertex vertices[] = { */
		/* 		Vertex(Vector2f(line.first.x, line.first.y)), */
		/* 		Vertex(Vector2f(line.second.x, line.second.y))}; */
		/* 	window.draw(vertices, 2, sf::Lines); */
		/* } */
		p->setPosition(this->x - this->r, this->y - this->r);
		window.draw(*p);
	}
} // namespace Object
