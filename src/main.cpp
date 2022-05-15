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
#include "include/Physics/Geometry.hpp"
#include "include/Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
/* using namespace std; */
using sf::Keyboard;
using Key = sf::Keyboard::Key;
const int WIDTH = 1000;
const int HEIGHT = 1000;
using Point = Geometry::Point<double>;
int main()
{
	std::mt19937 rng(
		std::chrono::steady_clock::now().time_since_epoch().count());

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
	std::unique_ptr<Player> player(
		new Player(WIDTH / 2, HEIGHT / 2, 10, WIDTH, HEIGHT));
	std::cout << "Creating window\n";
	std::vector<std::pair<Point, Point>> lines;
	lines.push_back({Point(0, 0), Point(WIDTH, 0)});
	lines.push_back({Point(0, 0), Point(0, HEIGHT)});
	lines.push_back({Point(0, HEIGHT), Point(WIDTH, HEIGHT)});
	lines.push_back({Point(WIDTH, 0), Point(WIDTH, HEIGHT)});
	/* lines.push_back({Point(100, 500), Point(200, 500)}); */
	const int N = 5;
	const int sides = 4;
	for (int i = 0; i < N; i++)
	{
		std::set<std::pair<int, int>> p;
		std::pair<int, int> pp;
		for (int j = 0; j < sides; j++)
		{
			do
			{
				pp = {rng() % WIDTH, rng() % HEIGHT};
			} while (p.find(pp) != p.end());
			p.insert(pp);
		}
		std::vector<std::pair<int, int>> temp(p.begin(), p.end());
		for (int j = 0; j < sides; j++)
		{
			lines.push_back({Point(temp[j].first, temp[j].second),
							 Point(temp[(j + 1) % sides].first,
								   temp[(j + 1) % sides].second)});
		}
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();
		if (event.type == sf::Event::LostFocus) continue;
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
		else if (Keyboard::isKeyPressed(Key::J))
		{
			player->rotatePlayer(0.2);
		}
		else if (Keyboard::isKeyPressed(Key::K))
		{
			player->rotatePlayer(-0.2);
		}
		window.clear();
		/* window.draw(shape); */
		player->draw(window, lines);
		window.display();
	}
	return 0;
}
