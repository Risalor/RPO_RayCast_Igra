#include "Enemy.h"

Enemy::Enemy(int spx, int spy, int tpx, int tpy) {
	eStartPos.x = spx;
	eStartPos.y = spy;
	eTargetPos.x = tpx;
	eTargetPos.y = tpy;
	ePos = eStartPos;

	eDir.x = 0;
	eDir.y = 1;

	eSpeed = 3.f;
	eRange = 15.f;
}

Enemy::~Enemy() {}

bool isVisible(const sf::Vector2f& pPos, const sf::Vector2f& ePos) {
    int pTileX = int(pPos.x);
	int pTileY = int(pPos.y);

    int eTileX = int(ePos.x);
	int eTileY = int(ePos.y);    

	if (eTileY < pTileY || (eTileY == pTileY && eTileX < pTileX)) {
		std::swap(pTileX, eTileX);
		std::swap(pTileY, eTileY);
	}

	int m = 2 * (eTileY - pTileY);
	int slopeError = m - (eTileX - pTileX);
	for (int x = pTileX, y = pTileY; x <= eTileX; x++) {
		
		if (glb::consts::worldMap[x][y] > 0) {
			return false;
		}

		slopeError += m;

		if (slopeError >= 0) {
			y++;
			slopeError -= 2 * (eTileX - pTileX);
		}
	}

    return true;
}

void Enemy::update(float dt, sf::Vector2f pPos) {

	sf::Vector2f pDistanceVector = pPos - ePos;
	float pDistance = std::sqrt(pDistanceVector.x * pDistanceVector.x + pDistanceVector.y * pDistanceVector.y);

	if (pDistance < eRange && isVisible(pPos, ePos)) {
		aggro(dt);
	}
	else {
		patrol(dt);
	}
}

void Enemy::patrol(float dt) {
	eDir = eTargetPos - ePos;

	float length = std::sqrt(eDir.x * eDir.x + eDir.y * eDir.y);
	eDir /= length;

	ePos += eDir * eSpeed * dt;

	if (std::sqrt((ePos.x - eTargetPos.x) * (ePos.x - eTargetPos.x) + (ePos.y - eTargetPos.y) * (ePos.y - eTargetPos.y)) < eSpeed * dt) {
		std::swap(eStartPos, eTargetPos);
		eDir = -eDir;
	}
}

void Enemy::aggro(float dt) {
	//std::cout << "ag ";
}

void Enemy::attack() {

}