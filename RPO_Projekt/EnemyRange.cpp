#include "EnemyRange.h"

EnemyRange::EnemyRange(int spx, int spy, int tpx, int tpy) : Enemy(spx, spy, tpx, tpy) {
	eHealth = 8;
	eSpeed = 2.f;
	eVision = 12.f;

	eRange = 6.f;
	eDamage = 3;

	eCooldown = 0.7f;

	eType = 1;
}

EnemyRange::~EnemyRange() {}

void EnemyRange::attack(Player& player) {
	eState = 3;

	Projectile* p = new Projectile(ePos, eDir, eDamage);
}













