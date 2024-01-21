#include "EnemyMelee.h"

EnemyMelee::EnemyMelee(int spx, int spy, int tpx, int tpy) : Enemy(spx, spy, tpx, tpy) {
	eHealth = 12;
	eSpeed = 3.2f;
	eVision = 10.f;

	eRange = 1;
	eDamage = 2;

	eCooldown = 1.2f;
	eType = 0;
}

EnemyMelee::~EnemyMelee() {}

void EnemyMelee::attack(Player& player) {
	eState = 3;

	player.takeDamage(eDamage);
}