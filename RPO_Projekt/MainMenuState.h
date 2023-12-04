#pragma once
#include "EditorState.h"

class MainMenuState : public State {
private:
	void initState();
	std::vector<Button> buttons;
	sf::SoundBuffer buffer;
	sf::Sound menuMusic;
	sf::RectangleShape background;
	sf::Texture tex;

	sf::Sprite mouse;
	sf::Texture mouse_up, mouse_down;
public:
	MainMenuState();
	~MainMenuState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);
};

