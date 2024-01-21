#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"
#include "Player.h"
#include "Projectile.h"
#include <iostream>

class Enemy {
protected:
	sf::Vector2f ePos;
	sf::Vector2f eDir;

	sf::Vector2f eStartPos;
	sf::Vector2f eTargetPos;

	sf::Clock attackTimer;

protected:

	int eHealth;

	float eSpeed;
	float eVision;
	float eRange;
	float eCooldown;

	float patrolPauseDuration;
	sf::Clock patrolTimer;

public:

	Enemy(int spx, int spy, int tpx, int tpy);
	~Enemy();

	sf::Vector2f getPos() const { return ePos; }
	int getHealth() { return eHealth; }
	void takeDamage(int damage);

	void update(float dt, Player& player);

	void patrol(float dt);
	void aggro(float dt, Player& player);
	virtual void attack(Player& player);
};