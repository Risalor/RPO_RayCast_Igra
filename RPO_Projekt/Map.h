#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <cmath>
#include <iostream>

class Map {
private:
	sf::Vector2f plane;
	void rayCastDraw(sf::RenderTarget* window, Player& pInfo);
	void draw2D(sf::RenderTarget* window, Player& pInfo);
public:
	Map();
	void draw(sf::RenderTarget* window, Player& pInfo);
};

