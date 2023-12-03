#include "MainMenuState.h"

void MainMenuState::initState() {
	buttons.push_back(Button(sf::Vector2f(screenWidth / 2 + 30, 50.f), "Start"));
	buttons.push_back(Button(sf::Vector2f(screenWidth / 2 + 30, 150.f), "Quit"));
}

MainMenuState::MainMenuState() : State() {
	initState();
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::update(float dt, sf::Vector2f mousePos) {
	buttons[0].update(mousePos);
	buttons[1].update(mousePos);
	
	if (buttons[0].clicked()) {
		State::trigger = StateTrigger::START_GAME;
	}

	if (buttons[1].clicked()) {
		State::trigger = StateTrigger::END_GAME;
	}
}

void MainMenuState::draw(sf::RenderTarget* window) {
	buttons[0].draw(window);
	buttons[1].draw(window);
}
