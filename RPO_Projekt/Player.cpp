#include "Player.h"
#include <iostream>



Player::Player(float speed) :movementSpeed(movementSpeed), rotationSpeed(rotationSpeed) {
	
    this->playerPos.x = 22;
    this->playerPos.y = 12;
	this->playerDir.x = 0;
	this->playerDir.y = 1;
	this->movementSpeed = 0.10f;
	this->rotationSpeed = 10.f;
	this->shiftPressed = false;
	this->shiftDelayTime = 1.4f;
	this->shiftTimeCount = 0.f;
	this->hp = 10;
}

Player::~Player() {

}

void Player::update(float dt) {
	move(dt);


}



void Player::move(float dt)
{

	shiftTimeCount += dt;
	//std::cout << movementSpeed << std::endl;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && !shiftPressed && shiftTimeCount >= shiftDelayTime) { //zagotovi , da po tekanju igralca le-ta nemore spet takoj tekati
		shiftDelayTime = 1.4f;
		shiftPressed = true;
		shiftTimeCount = 0.f;  // Ponastavi časovnik
		movementSpeed = 0.16f;
		rotationSpeed = 12.f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && shiftPressed && shiftTimeCount >= shiftDelayTime) { //zagotovi , da lahko igralec teka samo določen čas
		shiftPressed = false;
		shiftTimeCount = 0.f;  // Ponastavi časovnik
		movementSpeed = 0.10f;
		rotationSpeed = 10.f;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && shiftPressed && shiftTimeCount < shiftDelayTime) {//zagotovi , da uporabnik mora čakati da spet lahko teka tako dolgo, kot je prej tekal ampak ne več kot shiftDelayTime
		shiftDelayTime = shiftTimeCount;
		shiftPressed = false;
		shiftTimeCount = 0.f;
		movementSpeed = 0.10f;
		rotationSpeed = 10.f;
	}

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



