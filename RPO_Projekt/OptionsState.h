#pragma once

#include "Slider.h"

class OptionsState : public State {
private:
	void initState();
	std::vector<Slider> sliders;

	sf::Sprite mouse;
	sf::Texture mouse_up, mouse_down;

	sf::SoundBuffer buffer;
	sf::Sound music;

	Button button;

	sf::Text text;
	sf::Font font;
public:
	OptionsState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);
};

