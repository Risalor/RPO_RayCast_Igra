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

	plane.x = 0.66f;
	plane.y = 0.f;


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


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		if(checkBounds(1))
		equipItem(0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		if (checkBounds(2))
		equipItem(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		if (checkBounds(3))
		equipItem(2);
	}

}

void Player::updateEquipment(std::vector<Item*> item)
{
	for (int i = 0; i < item.size(); i++) {
		if (item[i] != nullptr) {
			//std::cout <<i<< ": " << item[i]->getName() << " " << item[i]->getPickedStatus() <<" " << item[i]->getEquiped() << std::endl;

			if ((getPos().x <= item[i]->getStartPos().x + 0.5 && getPos().x >= item[i]->getStartPos().x - 0.5)
				&& (getPos().y <= item[i]->getStartPos().y + 0.5 && getPos().y >= item[i]->getStartPos().y - 0.5)) {


				if (item[i]->getPickedStatus() == false) {
					item[i]->setPicked(true);
					item[i]->setEquiped(true);
					inventory.addItem(*item[i]);
					std::cout << "Dodan v inventory : " << item[i]->getName() << " Status equiped:  " << item[i]->getEquiped() << std::endl;

					std::cout << i << ": " << item[i]->getName() << " " << item[i]->getPickedStatus() << " " << item[i]->getEquiped() << std::endl;
					unequipOthers(item[i]->getName());

				}
			}
		}
		else {
			std::cout <<  "Neveljaven dostop " << std::endl;

		}
	}

}

void Player::equipItem(int itemIndex)
{
	
	if (itemIndex >= 0 && itemIndex <= inventory.getSize()) {
		std::cout << "Equipan item:  " << inventory[itemIndex].getName() << " Status e:  " << inventory[itemIndex].getEquiped() << std::endl;

		inventory[itemIndex].setEquiped(true);
		unequipOthers(inventory[itemIndex].getName());
		
	}
	
}

Weapon Player::getItem()
{

	Weapon* weapon = nullptr;
	for (int i = 0; i < inventory.getSize(); i++) {
		if (inventory[i].getEquiped()) {
			weapon = dynamic_cast<Weapon*>(&inventory[i]);
			if (weapon != nullptr) {
				break;
			}
		}
	}
	if (weapon != nullptr) {
		weapon->setValid(true);
		return *weapon;
	} else 
		throw std::runtime_error("No weapon equipped");


}

void Player::unequipOthers(const std::string& name)
{
	std::cout << "Velikost: " << inventory.getSize() << std::endl;
	for (int j = 0; j < inventory.getSize(); j++) {
		try {
			Item& item = inventory[j];
			if (item.getName() != name) {
				item.setEquiped(false);
				std::cout << "Unequipani itemi:  " << item.getName() << std::endl;
			}
		}
		catch (const char* msg) {
			std::cerr << "Exception caught in unequipOthers: " << msg << std::endl;
		}
	}
}

bool Player::checkBounds(int number)
{
	if (number <= inventory.getSize()) {
		return true;
	}
	else {
		return false;
	}
}

bool Player::inventoryEmpty()
{

	if (inventory.getSize() > 0)
		return true;
	else
		return false;
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
		sf::Vector2f oldPlane(plane);
		plane.x = plane.x * cos(-0.1f) - plane.y * sin(-0.1f);
		plane.y = oldPlane.x * sin(-0.1f) + plane.y * cos(-0.1f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sf::Vector2f oldPlane(plane);
		plane.x = plane.x * cos(0.1f) - plane.y * sin(0.1f);
		plane.y = oldPlane.x * sin(0.1f) + plane.y * cos(0.1f);
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

	float hpPercent = hp / maxHp * 100;

	healthBar.setSize(sf::Vector2f(hpPercent, 10.0));


}



