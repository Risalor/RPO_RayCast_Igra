#include "GamePlayState.h"

void GamePlayState::initState()  {
	player = Player(10.f);
	enemy.push_back(Enemy(2, 3, 6, 5));
	enemy.push_back(Enemy(6, 17, 7, 18));
}

GamePlayState::GamePlayState() : State() {
	initState();
}

GamePlayState::~GamePlayState() {

}

void GamePlayState::update(float dt) {
	player.update(dt);
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i].update(dt, player.getPos());	
	}
}

void GamePlayState::draw(sf::RenderTarget* window) {
	
	map.draw(window, player, enemy);
	
}
