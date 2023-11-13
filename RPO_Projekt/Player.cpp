#include "Player.h"



Player::Player(float speed) :movementSpeed(movementSpeed), rotationSpeed(rotationSpeed) {
	
    playerPos.x = 22;
    playerPos.y = 12;
	playerDir.x = 0;
	playerDir.y = 1;
	movementSpeed = 0.1f;
	rotationSpeed = 10.f;
}

Player::~Player() {

}

void Player::update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (glb::consts::worldMap[int(playerPos.x + playerDir.x)][int(playerPos.y)] == false) playerPos.x += playerDir.x * movementSpeed;
		if (glb::consts::worldMap[int(playerPos.x)][int(playerPos.y + playerDir.y)] == false) playerPos.y += playerDir.y * movementSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (glb::consts::worldMap[int(playerPos.x - playerDir.x)][int(playerPos.y)] == false) playerPos.x -= playerDir.x * movementSpeed;
		if (glb::consts::worldMap[int(playerPos.x)][int(playerPos.y - playerDir.y)] == false) playerPos.y -= playerDir.y * movementSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sf::Vector2f oldDirection = playerDir;
		float newDirectionX = oldDirection.x * std::cos(-0.1f) - oldDirection.y * std::sin(-0.1f);
		float newDirectionY = oldDirection.x * std::sin(-0.1f) + oldDirection.y * std::cos(-0.1f);
		playerDir.x = newDirectionX;
		playerDir.y = newDirectionY;
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sf::Vector2f oldDirection = playerDir;
		float newDirectionX = oldDirection.x * std::cos(0.1f) - oldDirection.y * std::sin(0.1f);
		float newDirectionY = oldDirection.x * std::sin(0.1f) + oldDirection.y * std::cos(0.1f);
		playerDir.x = newDirectionX;
		playerDir.y = newDirectionY;
		
	}
}



