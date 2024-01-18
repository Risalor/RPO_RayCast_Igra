#include "Slider.h"

Slider::Slider(sf::Vector2f pos, int value, std::string text) : pos(pos), value(value) {
	lineL.setSize(sf::Vector2f(value * 3, 2.f));
	lineL.setFillColor(sf::Color::White);
	lineL.setPosition(pos);

	lineR.setSize(sf::Vector2f(300 - value * 3, 2.f));
	lineR.setFillColor(sf::Color::Red);
	lineR.setPosition(sf::Vector2f(pos.x + value * 3, pos.y));

	slide.setRadius(5.f);
	slide.setFillColor(sf::Color::Green);
	slide.setPosition(sf::Vector2f(pos.x + value * 3, pos.y));
	slide.setOrigin(sf::Vector2f(5, 5));

	if (!font.loadFromFile("Assets/Fonts/font1.otf")) {
		std::cout << "Could not load";
	}

	sliText.setFont(font);
	sliText.setCharacterSize(20.f);
	sliText.setString(text);
	sliText.setPosition(sf::Vector2f(pos.x, pos.y + 5));

	valText.setFont(font);
	valText.setCharacterSize(20.f);
	valText.setString(std::to_string(value));
	valText.setPosition(sf::Vector2f(pos.x + 280, pos.y + 5));
}

void Slider::update(sf::Vector2f mousePos) {
	if (mousePos.x > pos.x && mousePos.x < pos.x + 303 && mousePos.y > pos.y - 15 && mousePos.y < pos.y + 15) {
		slide.setPosition(sf::Vector2f(mousePos.x, pos.y));
		value = (mousePos.x - pos.x) / 3;
		lineL.setSize(sf::Vector2f(value * 3, 2.f));
		lineR.setSize(sf::Vector2f(300 - value * 3, 2.f));
		lineR.setPosition(sf::Vector2f(pos.x + value * 3, pos.y));
		valText.setString(std::to_string(value));
	}
}

void Slider::draw(sf::RenderTarget* window) {
	window->draw(lineL);
	window->draw(lineR);

	sliText.setFont(font);
	window->draw(sliText);

	valText.setFont(font);
	window->draw(valText);

	window->draw(slide);
}

int Slider::getValue() {
	return value;
}
