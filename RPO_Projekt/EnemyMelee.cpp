#include "EnemyMelee.h"

EnemyMelee::EnemyMelee(int spx, int spy, int tpx, int tpy) : Enemy(spx, spy, tpx, tpy) {
	eSpeed = 4.f;
	eVision = 10.f;
	eRange = 0.5;
}

EnemyMelee::~EnemyMelee() {}

void EnemyMelee::attack() {

}