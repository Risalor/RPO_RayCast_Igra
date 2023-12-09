#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "EnemyRange.h"
#include "EnemyMelee.h"
#include <cmath>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

struct HorizontalLine {
	int x;
	int start;
	int end;
	int texX;
	double texStep;
	double texPos;
};

struct Wall {
	std::vector<HorizontalLine> line;
	int texNum;
	int wallDist1;
	int wallDist2;
};

class Map {
private:
	sf::Vector2f plane;
	void rayCastDraw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy*> eInfo);
	void draw2D(sf::RenderTarget* window, Player& pInfo , std::vector<Enemy*> eInfo);
	std::vector<sf::Image> images;
	std::vector<std::vector<sf::Color>> texture;
public:
	Map();
	void draw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy*> eInfo);
};

