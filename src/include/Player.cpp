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
        if (x + amt + r >= w || x + amt <= r)
            return;
        x += amt;
    }
    void Player::moveY(double amt)
    {
        if (y + amt + r >= h || y + amt <= r)
            return;
        y += amt;
    }
    void Player::moveRight() { moveX(DELTA); }
    void Player::moveLeft() { moveX(-DELTA); }
    void Player::moveDown() { moveY(DELTA); }
    void Player::moveUp() { moveY(-DELTA); }
    void Player::draw(sf::RenderWindow &window)
    {
        unique_ptr<sf::CircleShape> p(new sf::CircleShape(this->r, POINT_COUNT));
        Vertex origin(Vector2f(this->x, this->y));
        p->setOrigin(this->x, this->y);
        vector<Vertex> end_points;
        for (int i = 0; i < FOV; i += DTHETA)
        {
            pair<double, double> end_point;
            double m = tan(i); // slope of the ray
            double y1 = this->y, x1 = this->x;
            const vector<pair<double, double>> a = {{y1 / m, y1},
                                                    {-x1, -m * x1},
                                                    {w - x1, m * (w - x1)},
                                                    {(h - y1) / m, h - y1}};
            debug(x1, y1, i, m);
            debug(a);
            for (auto &[x, y] : a)
            {
                if (x >= 0 && x <= w && y >= 0 && y <= h)
                {
                    // this is the endpoint of the ray;
                    end_point = {x, y};
                    double theta = atan(y / x);
                    if (std::abs(theta - i) <= EPSILON)
                        break;
                }
            }
            end_points.push_back(
                Vertex(Vector2f(end_point.first + x1, y1 + end_point.second)));
        }
        for (auto &e : end_points)
        {
            sf::Vertex vertices[] = {origin, e};
            window.draw(vertices, 2, sf::Lines);
        }
        window.draw(*p);
    }
} // namespace Object
