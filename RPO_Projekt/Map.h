#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Enemy.h"
#include "EnemyRange.h"
#include "EnemyMelee.h"
#include "Projectile.h"
#include "SpriteManager.h"
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
	int side;
};

struct Entity {
	sf::Sprite* sprite;
	float distance;
};

class Map {
private:
	sf::Vector2f plane;
	void rayCastDraw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy*> eInfo, std::vector<Projectile*> prInfo);
	void draw2D(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy*> eInfo, std::vector<Projectile*> prInfo, std::vector<Item*> itemStartPos);
	std::vector<sf::Texture> textures;
	std::vector<sf::Texture> darkTextures;
	std::vector<std::vector<sf::Color>> texture;
	SpriteManager spriteManager;
	void handleDoor(Player& pInfo);
public:
	Map();
	void draw(sf::RenderTarget* window, Player& pInfo, std::vector<Enemy*> eInfo, std::vector<Projectile*> prInfo, std::vector<Item*> itemStartPos);
};

