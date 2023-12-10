#include "Projectile.h"
#include "GamePlayState.h"

Projectile::Projectile(sf::Vector2f prPos, sf::Vector2f prDir, int damage) {
	this->prPos = prPos;
	this->prDir = prDir;

	this->damage = damage;
	this->prSpeed = 2;
	
	GamePlayState::addProjectile(this);
}

Projectile::~Projectile() {
	GamePlayState::removeProjectile(this);
}

void Projectile::update(float dt, Player& player) {
	prPos += prDir * prSpeed * dt;

	if (std::abs(player.getPos().x - prPos.x) <= 0.4f && std::abs(player.getPos().y - prPos.y) <= 0.4f) {
		player.takeDamage(damage);
		delete this;
		return;
	}

	if (timer.getElapsedTime().asSeconds() > 5) {
		delete this; 
		return;
	}
}