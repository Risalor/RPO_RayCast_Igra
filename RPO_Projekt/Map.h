#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <cmath>
#include <iostream>

class Map {
private:
	sf::Vector2f plane;
public:
	Map();
	void draw(sf::RenderTarget* window, Player& pInfo);

};

