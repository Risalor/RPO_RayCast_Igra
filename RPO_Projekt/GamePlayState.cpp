#include "GamePlayState.h"

void GamePlayState::initState()  {
	player = Player(10.f);
}

GamePlayState::GamePlayState() : State() {
	initState();
}

GamePlayState::~GamePlayState() {

}

void GamePlayState::update(float dt) {
	player.update(dt);
	
}

void GamePlayState::draw(sf::RenderTarget* window) {
	
	map.draw(window, player);
	
}
