#pragma once
#include "Enemy.h"


class EnemyMelee : public Enemy {
private:
    int eDamage;
public:
    EnemyMelee(int spx, int spy, int tpx, int tpy);
    ~EnemyMelee();

    void attack() override;
};
#pragma once
