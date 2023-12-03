#include "Button.h"

void Button::initTex() {
	
	if (!tex_def.loadFromFile("Assets/Buttons/button2.png")) {
		std::cout << "No Tex";
	}

	if (!tex_hov.loadFromFile("Assets/Buttons/button1.png")) {
		std::cout << "No Tex";
	}

	tex_hov.setSmooth(true);
	tex_def.setSmooth(true);
	btn.setTexture(tex_def);

	if (!font.loadFromFile("Assets/Fonts/font1.ttf")) {
		std::cout << "No font";
	}
}

Button::Button(sf::Vector2f pos, std::string buttonText) {

	if (!buffer.loadFromFile("Assets/Buttons/button.wav")) {
		std::cout << "Unable to load sound";
	}

	text.setFont(font);
	text.setCharacterSize(20.f);
	text.setString(buttonText);
	text.setPosition(sf::Vector2f(pos.x + 92.f, pos.y + 40.f));

	initTex();
	btn.setPosition(pos);
	btn.setScale(1.3f, 1.3f);
	state = btnState::DEFAULT;
	playSound = false;
}

Button::~Button() {
}

void Button::draw(sf::RenderTarget* window) {
	if (state == btnState::HOVER) {
		btn.setTexture(tex_hov);
	} else {
		btn.setTexture(tex_def);
	}
	window->draw(btn);
	text.setFont(font);
	window->draw(text);
}

void Button::update(sf::Vector2f mouseCoord) {
	if (btn.getGlobalBounds().contains(mouseCoord)) {
		state = btnState::HOVER;
		if (sound.getStatus() == sf::Sound::Status::Stopped && playSound) {
			playSound = false;
			sound.setBuffer(buffer);
			sound.play();
		}
	} else {
		playSound = true;
		state = btnState::DEFAULT;
	}

	if (btn.getGlobalBounds().contains(mouseCoord) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		state = btnState::CLICKED;
	}
}

bool Button::clicked() const {
	if (state == btnState::CLICKED) {
		return true;
	} 
	
	return false;
}
