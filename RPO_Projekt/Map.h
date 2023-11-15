#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <cmath>
#include <iostream>

class Map {
private:
	sf::Vector2f plane;
	void rayCastDraw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy>& eInfo);
	void draw2D(sf::RenderTarget* window, Player& pInfo , std::vector<Enemy>& eInfo);
	std::vector<sf::Color> texture;
public:
	Map();
	void draw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy>& eInfo);
};

