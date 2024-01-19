#pragma once

#include "MainMenuState.h"

class Slider {
private:
	sf::RectangleShape lineL, lineR;
	sf::CircleShape slide;
	sf::Vector2f pos;
	int value;
	sf::Text sliText, valText;
	sf::Font font;

public:
	Slider(sf::Vector2f pos, int value, std::string text);
	void update(sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);
	int getValue();
};

