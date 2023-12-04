#pragma once
#include "Map.h"

enum btnState { DEFAULT, HOVER, CLICKED};

class Button {
private:
	sf::Sprite btn;
	sf::Texture tex_def;
	sf::Texture tex_hov;
	btnState state;
	sf::Font font;
	sf::Text text;
	sf::SoundBuffer hoverBuffer;
	sf::SoundBuffer pressedBuffer;
	sf::Sound soundHover, soundPressed;
	bool playSound;
	void initTex();
public:
	Button(sf::Vector2f pos, std::string text);
	~Button();
	void draw(sf::RenderTarget* window);
	void update(sf::Vector2f mouseCoord);
	bool clicked();
};