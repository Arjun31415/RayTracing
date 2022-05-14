/**
 * @file Player.hpp
 * @author Arjun
 * @brief Player class header file
 * @version 0.1
 * @date 2022-05-13
 *
 */
#pragma once
#include "Geometry.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <memory>
#include <vector>
inline namespace Object
{
  constexpr const double EPSILON = 1e-7;
  class Player
  {
    double x, y, r;
    constexpr const static double DELTA = 0.5;
    const static unsigned int POINT_COUNT = 50;
    constexpr const static int FOV = 180;
    const static unsigned int DTHETA = 2;
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
    void
    draw(sf::RenderWindow &,
         const std::vector<
             std::pair<Geometry::Point<double>, Geometry::Point<double>>> &);
  };
} // namespace Object
