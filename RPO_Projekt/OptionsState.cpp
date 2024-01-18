#include "OptionsState.h"

void OptionsState::initState() {

	std::fstream file("Assets/conf.bin", std::ios::in | std::ios::binary);

	int temp;

	file.read(reinterpret_cast<char*>(&temp), sizeof(int));
	sliders.push_back(Slider(sf::Vector2f(140, 120), temp, "Gameplay sound"));

	file.read(reinterpret_cast<char*>(&temp), sizeof(int));
	sliders.push_back(Slider(sf::Vector2f(140, 160), temp, "Editor sound"));

	file.read(reinterpret_cast<char*>(&temp), sizeof(int));
	sliders.push_back(Slider(sf::Vector2f(140, 200), temp, "Menu sound"));

	file.read(reinterpret_cast<char*>(&temp), sizeof(int));
	sliders.push_back(Slider(sf::Vector2f(140, 240), temp, "options sound"));

	file.close();

	button = Button(sf::Vector2f(500, 300), "Save&Quit");
	button.setScale(1.f);

	if (!mouse_up.loadFromFile("Assets/Cursor/cursor.gif")) {
		std::cout << "Cannot load texture\n";
	}

	if (!mouse_down.loadFromFile("Assets/Cursor/cursor_down.gif")) {
		std::cout << "Cannot load texture\n";
	}

	if (!buffer.loadFromFile("Assets/Music/options.wav")) {
		std::cout << "Faildes to load soundBuffer\n";
	}

	music.setBuffer(buffer);
	music.play();

	music.setLoop(true);
	music.setVolume(20.f);

	if (!font.loadFromFile("Assets/Fonts/font1.otf")) {
		std::cout << "Could not load";
	}

	text.setFont(font);
	text.setCharacterSize(40.f);
	text.setString("Options");
	text.setPosition(sf::Vector2f(50.f, 50.f));
}

OptionsState::OptionsState() : State() {
	initState();
}

void OptionsState::update(float dt, sf::Vector2f mousePos) {
	mouse.setPosition(mousePos);
	button.update(mousePos);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouse.setTexture(mouse_down);
	} else {
		mouse.setTexture(mouse_up);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		for (auto& it : sliders) {
			it.update(mousePos);
		}
	}

	music.setVolume(sliders.at(3).getValue());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || button.clicked()) {

		std::fstream file("Assets/conf.bin", std::ios::out | std::ios::binary);

		for (auto it : sliders) {
			int temp = it.getValue();
			file.write(reinterpret_cast<const char*>(&temp), sizeof(int));
		}

		file.close();

		State::trigger = END_STATE;
		music.stop();
	}
}

void OptionsState::draw(sf::RenderTarget* window) {
	for (auto& it : sliders) {
		it.draw(window);
	}

	button.draw(window);

	text.setFont(font);
	window->draw(text);

	window->draw(mouse);
}
