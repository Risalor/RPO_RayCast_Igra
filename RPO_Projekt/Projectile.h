#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "global.h"

class Projectile {
private:
	sf::Vector2f prPos;
	sf::Vector2f prDir;

	sf::Clock timer;

	float prSpeed;
	int damage;

public:
	Projectile(sf::Vector2f prPos, sf::Vector2f prDir, int damage);
	~Projectile();

	sf::Vector2f getPos() const { return prPos; }

	void update(float dt, Player& player);

};

