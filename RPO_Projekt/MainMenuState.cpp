#include "MainMenuState.h"

void MainMenuState::initState() {
	buttons.push_back(Button(sf::Vector2f(150.f, 50.f), "Start"));
	buttons.push_back(Button(sf::Vector2f(150.f, 150.f), "Editor"));
	buttons.push_back(Button(sf::Vector2f(150.f, 350.f), "Quit"));
	buttons.push_back(Button(sf::Vector2f(150.f, 250.f), "Options"));

	if (!buffer.loadFromFile("Assets/Music/MainMenu.wav")) {
		std::cout << "Cannot load music\n";
	}

	menuMusic.setBuffer(buffer);

	std::fstream file("Assets/conf.bin", std::ios::in | std::ios::binary);
	int temp;
	file.read(reinterpret_cast<char*>(&temp), sizeof(int));
	file.read(reinterpret_cast<char*>(&temp), sizeof(int));
	file.read(reinterpret_cast<char*>(&temp), sizeof(int));
	file.close();

	menuMusic.setVolume(temp);

	menuMusic.play();

	background.setSize(sf::Vector2f(screenWidth + 411.42f, screenHeight));
	tex.loadFromFile("Assets/Backgrounds/MenuBackground.png");
	background.setTexture(&tex);

	if (!mouse_up.loadFromFile("Assets/Cursor/cursor.gif")) {
		std::cout << "Cannot load texture\n";
	}

	if (!mouse_down.loadFromFile("Assets/Cursor/cursor_down.gif")) {
		std::cout << "Cannot load texture\n";
	}
}

MainMenuState::MainMenuState() : State() {
	initState();
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::update(float dt, sf::Vector2f mousePos) {
	buttons[0].update(mousePos);
	buttons[1].update(mousePos);
	buttons[2].update(mousePos);
	buttons[3].update(mousePos);

	mouse.setPosition(mousePos);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouse.setTexture(mouse_down);
	} else {
		mouse.setTexture(mouse_up);
	}

	if (menuMusic.getStatus() == sf::Sound::Status::Stopped) {
		if (!buffer.loadFromFile("Assets/Music/MainMenu.wav")) {
			std::cout << "Cannot load music\n";
		}

		std::fstream file("Assets/conf.bin", std::ios::in | std::ios::binary);
		int temp;
		file.read(reinterpret_cast<char*>(&temp), sizeof(int));
		file.read(reinterpret_cast<char*>(&temp), sizeof(int));
		file.read(reinterpret_cast<char*>(&temp), sizeof(int));
		file.close();

		menuMusic.setVolume(temp);

		menuMusic.setBuffer(buffer);
		menuMusic.play();
	}
	
	if (buttons[0].clicked()) {
		State::trigger = StateTrigger::START_GAME;
		menuMusic.stop();
	}

	if (buttons[1].clicked()) {
		State::trigger = StateTrigger::START_EDITOR;
		menuMusic.stop();
	}

	if (buttons[2].clicked()) {
		State::trigger = StateTrigger::END_GAME;
		menuMusic.stop();
	}

	if (buttons[3].clicked()) {
		State::trigger = StateTrigger::START_OPTIONS;
		menuMusic.stop();
	}
}

void MainMenuState::draw(sf::RenderTarget* window) {
	window->draw(background);
	buttons[0].draw(window);
	buttons[1].draw(window);
	buttons[2].draw(window);
	buttons[3].draw(window);
	window->draw(mouse);
}
