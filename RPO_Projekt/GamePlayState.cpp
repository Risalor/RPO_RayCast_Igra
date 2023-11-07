#include "GamePlayState.h"

void GamePlayState::initState() {
	shape.setRadius(100.f);
	shape.setFillColor(sf::Color::Green);
}

GamePlayState::GamePlayState() : State() {
	initState();
}

GamePlayState::~GamePlayState() {

}

void GamePlayState::update(float dt) {
	shape.setPosition(shape.getPosition().x + 1.f * dt, shape.getPosition().y + 1.f * dt);
}

void GamePlayState::draw(sf::RenderTarget* window) {
	window->draw(shape);
}
