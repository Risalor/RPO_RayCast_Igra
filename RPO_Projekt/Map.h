#pragma once

#include <SFML/Graphics.hpp>
#include "global.h"
#include <cmath>
#include <iostream>

class Map {
private:
	sf::Vector2f playerPos;
	sf::Vector2f playerDir;
	float playerAng;
	sf::Vector2f plane;
public:
	Map();
	void draw(sf::RenderTarget* window);

};

