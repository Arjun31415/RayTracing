#include "Player.hpp"
#include "debug/debug.hpp"
using std::pair;
using std::unique_ptr;

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
    p->setPosition(this->x, this->y);
    window.draw(*p);
}
