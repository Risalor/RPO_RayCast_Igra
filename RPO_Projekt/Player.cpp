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
	this->maxHp = 10;
	this->hp = maxHp;


	this->isInventoryVisible = false;
	healthBar.setSize(sf::Vector2f(100.0, 10.0)); // Dolžina 100, višina 10
	healthBar.setFillColor(sf::Color::Green);

	healthBarBackground.setSize(sf::Vector2f(100.0, 10.0));
	healthBarBackground.setFillColor(sf::Color(128, 128, 128)); // Siva barva


}

Player::~Player() {

}

void Player::update(float dt) {
	move(dt);
	updateHealthBar();
	if (this->hp <= 0) {
		std::cout << "player DEAD\n";
	}
}

void Player::updateEquipment(std::vector<Item*> item)
{


	for (int i = 0; i < item.size(); i++) {
		/*std::cout << "X: " << item[i]->getStartPos().x << "   Y: " << item[i]->getStartPos().y << std::endl;
		std::cout << "XX: " << getPos().x << "   YY: " << getPos().y << std::endl;*/
		
		if ((getPos().x <=item[i]->getStartPos().x + 0.5 && getPos().x >= item[i]->getStartPos().x - 0.5)
			&& (getPos().y <= item[i]->getStartPos().y + 0.5 && getPos().y >= item[i]->getStartPos().y - 0.5)) {
		

			if (item[i]->getPickedStatus() == false) {
				inventory.addItem(*item[i]);
				item[i]->setPicked(true);
				for(int j=0;j<inventory.getSize();j++)
				std::cout << "Items in inventory : " << inventory[j].debugPrint() << std::endl;
			}
		}
	}

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





void Player::renderHealthBar(sf::RenderTarget* window) {
	// Pridobi trenutno velikost okna
	sf::Vector2u windowSize = window->getSize();

	float margin = 10;

	// Nastavi x pozicijo na levi rob z nekim robom
	float xPosition = margin;

	float yPosition = windowSize.y - windowSize.y + 10;

	healthBar.setPosition(xPosition, yPosition);
	healthBarBackground.setPosition(xPosition, yPosition);
	// Nariši healthbar
	window->draw(healthBarBackground);
	window->draw(healthBar);

}

void Player::showInventory(sf::RenderTarget* window)
{
	isInventoryVisible = !isInventoryVisible;
	if (!inventoryTexture.loadFromFile("Assets/Inventory/inventory.png")) {
		std::cout << "Napaka pri odpiranju!" << std::endl;
	}
	else {

		inventorySprite.setTexture(inventoryTexture);
		inventorySprite.setPosition(0, 10);
		window->draw(inventorySprite);

	}
}



void Player::updateHealthBar() {

	// Posodobi dolžino zdravstvene vrstice glede na trenutno hp

	float hpPercent = hp / maxHp * 100;

	healthBar.setSize(sf::Vector2f(hpPercent, 10.0));


}



