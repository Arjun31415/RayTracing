#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>
class Player
{
    double x, y, r;
    constexpr const static double DELTA = 0.5;
    const static unsigned int POINT_COUNT = 50;
    double w, h;
    void moveX(double);
    void moveY(double);

  public:
    Player();
    Player(double, double, double);
    Player(double, double, double, double, double);
    void setPosition(double x, double y);
    std::pair<double, double> getPosition();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void draw(sf::RenderWindow &);
};
