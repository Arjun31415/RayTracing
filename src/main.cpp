/**
 * @file main.cpp
 * @author Arjun
 * @brief Main file for executing of ray-tracing
 * @version 0.1
 * @date 2022-05-13
 *
 *
 */
#define debugging
#include "include/Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>
using namespace std;
using sf::Keyboard;
using Key = sf::Keyboard::Key;
const int WIDTH = 1000;
const int HEIGHT = 1000;
int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
    unique_ptr<Player> player(
        new Player(WIDTH / 2, HEIGHT / 2, 5, WIDTH, HEIGHT));
    cout << "Creating window\n";
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        if (event.type == sf::Event::LostFocus)
            continue;
        if (Keyboard::isKeyPressed(Key::W))
        {
            player->moveUp();
        }
        else if (Keyboard::isKeyPressed(Key::S))
        {
            player->moveDown();
        }
        else if (Keyboard::isKeyPressed(Key::A))
        {
            player->moveLeft();
        }
        else if (Keyboard::isKeyPressed(Key::D))
        {
            player->moveRight();
        }
        window.clear();
        /* window.draw(shape); */
        player->draw(window);
        window.display();
    }
    return 0;
}
