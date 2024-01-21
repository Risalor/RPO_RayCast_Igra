#include "Enemy.h"
#include "GamePlayState.h"

Enemy::Enemy(int spx, int spy, int tpx, int tpy) {
	eStartPos.x = spx;
	eStartPos.y = spy;
	eTargetPos.x = tpx;
	eTargetPos.y = tpy;
	ePos = eStartPos;

	eDir.x = 0;
	eDir.y = 1;

	eHealth = 10;
	eSpeed = 3.f;
	eVision = 12.f;
	eRange = 1.f;

    ePatrolPause = 0.1f;
    eState = 0;
}

Enemy::~Enemy() {
	GamePlayState::removeEnemy(this);
}

void Enemy::takeDamage(int damage) {
	this->eHealth -= damage;

	if (this->eHealth <= 0) {
		delete this;
	}
}

bool isVisible(const sf::Vector2f& pPos, const sf::Vector2f& ePos) {
    int pTileX = static_cast<int>(pPos.x);
    int pTileY = static_cast<int>(pPos.y);

    int eTileX = static_cast<int>(ePos.x);
    int eTileY = static_cast<int>(ePos.y);

    int dx = abs(eTileX - pTileX);
    int dy = abs(eTileY - pTileY);
    int sx = (pTileX < eTileX) ? 1 : -1;
    int sy = (pTileY < eTileY) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (pTileX == eTileX && pTileY == eTileY) {
            break;
        }

        if (pTileX >= 0 && pTileY >= 0 && pTileX < glb::consts::worldMap.size() && pTileY < glb::consts::worldMap[0].size() && glb::consts::worldMap[pTileY][pTileX] > 0) {
            return false;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            pTileX += sx;
        }
        if (e2 < dx) {
            err += dx;
            pTileY += sy;
        }
    }

    return true;
}

void Enemy::update(float dt, Player& player) {

    sf::Vector2f pPos = player.getPos();

    sf::Vector2f pDistanceVector = pPos - ePos;
    float pDistance = std::sqrt(pDistanceVector.x * pDistanceVector.x + pDistanceVector.y * pDistanceVector.y);

    if (pDistance < eVision && isVisible(pPos, ePos)) {
        eTargetPos = pPos;
        aggro(dt, player);
    }
    else {
        patrol(dt);
    }
}

void Enemy::patrol(float dt) {
    eState = 0;

    eDir = eTargetPos - ePos;
    float length = std::sqrt(eDir.x * eDir.x + eDir.y * eDir.y);

    if (length > 0) {
        eDir /= length;

        float nextX = (ePos.x + eDir.x + 0.5f);
        float nextY = (ePos.y + eDir.y + 0.5f);

        if (patrolTimer.getElapsedTime().asSeconds() < ePatrolPause) {
            return;
        }

        if (nextX >= 0 && nextY >= 0 && nextX < glb::consts::worldMap[0].size() && nextY < glb::consts::worldMap.size() && glb::consts::worldMap[nextY][nextX] == 0) {
            ePos += eDir * eSpeed * dt;
        }
        else {
            patrolTimer.restart();
            std::swap(eStartPos, eTargetPos);
        }

        if (std::sqrt((ePos.x - eTargetPos.x) * (ePos.x - eTargetPos.x) + (ePos.y - eTargetPos.y) * (ePos.y - eTargetPos.y)) < eSpeed * dt) {
            patrolTimer.restart();
            std::swap(eStartPos, eTargetPos);
        }
    }
}


void Enemy::aggro(float dt, Player& player) {
    eState = 1;

    eDir = eTargetPos - ePos;
    float length = std::sqrt(eDir.x * eDir.x + eDir.y * eDir.y);

    if (length > 0) {
        eDir /= length;

        if (abs(ePos.x - eTargetPos.x) < eRange && abs(ePos.y - eTargetPos.y) < eRange) {
            if (attackTimer.getElapsedTime().asSeconds() >= eCooldown) {
                attack(player);
                attackTimer.restart();
            }
            return;
        }

        int nextX = static_cast<int>(ePos.x + eDir.x + 0.5f);
        int nextY = static_cast<int>(ePos.y + eDir.y + 0.5f);

        if (nextX >= 0 && nextY >= 0 && nextX < glb::consts::worldMap[0].size() && nextY < glb::consts::worldMap.size() && glb::consts::worldMap[nextY][nextX] == 0) {
            ePos += eDir * eSpeed * dt;
        }
    }
}

void Enemy::attack(Player& player) {
    eState = 3;
}