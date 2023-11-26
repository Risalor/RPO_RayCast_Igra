#pragma once
#include "Enemy.h"

class EnemyRange : public Enemy {
private:
    int eAmo;
    int eDamage;
public:
	EnemyRange(int spx, int spy, int tpx, int tpy);
    ~EnemyRange();

    void attack() override;
};
