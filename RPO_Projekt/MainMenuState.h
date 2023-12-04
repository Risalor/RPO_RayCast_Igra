#pragma once
#include "GamePlayState.h"

class MainMenuState : public State {
private:
	void initState();
	std::vector<Button> buttons;
	sf::SoundBuffer buffer;
	sf::Sound menuMusic;
	sf::RectangleShape background;
	sf::Texture tex;
public:
	MainMenuState();
	~MainMenuState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);
};

