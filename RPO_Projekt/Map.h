#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <cmath>
#include <iostream>
#include <filesystem>

class Map {
private:
	sf::Vector2f plane;
	void rayCastDraw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy>& eInfo);
	void draw2D(sf::RenderTarget* window, Player& pInfo , std::vector<Enemy>& eInfo);
	std::vector<sf::Image> images;
	std::vector<std::vector<sf::Color>> texture;
public:
	Map();
	void draw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy>& eInfo);
};

