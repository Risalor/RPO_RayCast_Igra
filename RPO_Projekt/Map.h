#pragma once

#include <SFML/Graphics.hpp>
#include "global.h"

class Map {
private:
	sf::Vector2f playerPos;
	sf::Vector2f playerDir;
	sf::Vector2f plane;
public:
	Map();
	void draw(sf::RenderTarget* window);

};

