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
	eVision = 12.f;
	eRange = 1.f;
}

Enemy::~Enemy() {}

bool isVisible(const sf::Vector2f& pPos, const sf::Vector2f& ePos) {
	int pTileX = int(pPos.x);
	int pTileY = int(pPos.y);
				 
	int eTileX = int(ePos.x);
	int eTileY = int(ePos.y);

	int dx = abs(eTileX - pTileX);
	int dy = abs(eTileY - pTileY);
	int sx = (pTileX < eTileX) ? 1 : -1;
	int sy = (pTileY < eTileY) ? 1 : -1;
	int err = dx - dy;

	while (true) {
		if (pTileX == eTileX && pTileY == eTileY) {
			break;
		}

		if (pTileX >= 0 && pTileY >= 0 && pTileX < mapWidth && pTileY < mapHeight && glb::consts::worldMap[pTileX][pTileY] > 0) {
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

void Enemy::update(float dt, Player &player) {
	
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
	eDir = eTargetPos - ePos;

	float length = std::sqrt(eDir.x * eDir.x + eDir.y * eDir.y);
	eDir /= length;

	if (glb::consts::worldMap[int(ePos.x + eDir.x)][int(ePos.y + eDir.y)] == false) {
		ePos += eDir * eSpeed * dt;
	}
	else {
		std::swap(eStartPos, eTargetPos);
	}

	if (std::sqrt((ePos.x - eTargetPos.x) * (ePos.x - eTargetPos.x) + (ePos.y - eTargetPos.y) * (ePos.y - eTargetPos.y)) < eSpeed * dt) {
		std::swap(eStartPos, eTargetPos); 
	}
}

void Enemy::aggro(float dt, Player& player) {
	eDir = eTargetPos - ePos;

	float length = std::sqrt(eDir.x * eDir.x + eDir.y * eDir.y);
	eDir /= length;

	if (abs(ePos.x - eTargetPos.x) < eRange && abs(ePos.y - eTargetPos.y) < eRange) {
		
		if (attackTimer.getElapsedTime().asSeconds() >= eCooldown) {
			attack(player);
			attackTimer.restart();
		}
		return;
	}

	if (glb::consts::worldMap[int(ePos.x + eDir.x)][int(ePos.y + eDir.y)] == false) {
		ePos += eDir * eSpeed * dt;
	}
}

void Enemy::attack(Player& player) {
	
}