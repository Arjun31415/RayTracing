#include "Player.hpp"
#include <vector>

using std::pair;

Player::Player()
{
    x = 0;
    y = 0;
    r = 0;
}
Player::Player(int x, int y, int r)
{
    this->x = x;
    this->y = y;
    this->r = r;
}
void Player::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}
pair<int, int> Player::getPosition() { return {x, y}; }
void Player::moveX() { x += DELTA; }
