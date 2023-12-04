#include "MainMenuState.h"

void MainMenuState::initState() {
	buttons.push_back(Button(sf::Vector2f(150.f, 150.f), "Start"));
	buttons.push_back(Button(sf::Vector2f(150.f, 250.f), "Quit"));

	if (!buffer.loadFromFile("Assets/Music/MainMenu.wav")) {
		std::cout << "Cannot load music\n";
	}

	menuMusic.setBuffer(buffer);
	menuMusic.play();

	background.setSize(sf::Vector2f(screenWidth + 411.42f, screenHeight));
	tex.loadFromFile("Assets/Backgrounds/MenuBackground.png");
	background.setTexture(&tex);
}

MainMenuState::MainMenuState() : State() {
	initState();
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::update(float dt, sf::Vector2f mousePos) {
	buttons[0].update(mousePos);
	buttons[1].update(mousePos);

	if (menuMusic.getStatus() == sf::Sound::Status::Stopped) {
		if (!buffer.loadFromFile("Assets/Music/MainMenu.wav")) {
			std::cout << "Cannot load music\n";
		}

		menuMusic.setBuffer(buffer);
		menuMusic.play();
	}
	
	if (buttons[0].clicked()) {
		State::trigger = StateTrigger::START_GAME;
		menuMusic.stop();
	}

	if (buttons[1].clicked()) {
		State::trigger = StateTrigger::END_GAME;
		menuMusic.stop();
	}
}

void MainMenuState::draw(sf::RenderTarget* window) {
	window->draw(background);
	buttons[0].draw(window);
	buttons[1].draw(window);
}
