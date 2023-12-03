#include "GamePlayState.h"

void GamePlayState::initState() {
	player = Player(10.f);
	enemy.push_back(new EnemyMelee(2, 3, 6, 5));
	enemy.push_back(new EnemyRange(6, 17, 7, 18));
	Inventory inv;
	inv.addItem(Weapon(0,10,"sword"));
	inv.addItem(Weapon(0, 10, "AK-47"));
	inv.addItem(Weapon(0, 10, "M4"));
	inv.addItem(Armor( 10, "chest"));
	inv.addItem(Armor( 10, "head"));
	inv.addItem(Armor( 10, "blaa"));
	

	/*for (size_t i = 0;i < inv.getSize();i++) {
		std::cout << inv[i].debugPrint() << std::endl;
	}*/

	
}

GamePlayState::GamePlayState() : State() {
	initState();
}

GamePlayState::~GamePlayState() {

}

void GamePlayState::update(float dt, sf::Vector2f mousePos) {
	player.update(dt);
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->update(dt, player.getPos());	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		State::trigger = StateTrigger::END_STATE;
	}
}

void GamePlayState::draw(sf::RenderTarget* window) {
	
	map.draw(window, player, enemy);
	
}
