#pragma once
#include "GamePlayState.h"

struct MapTile {
	int texNum;
	sf::Vector2f pos;
	sf::RectangleShape rect;
	sf::Texture tex;

	MapTile(int texNum, sf::Vector2f pos) : texNum(texNum), pos(pos) {
		rect.setSize(sf::Vector2f(17.f, 17.f));
		rect.setPosition(pos);
		rect.setFillColor(sf::Color::Green);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(1.f);
	}

	MapTile(int texNum, sf::Vector2f pos, sf::Texture tex) : texNum(texNum), pos(pos), tex(tex) {
		rect.setSize(sf::Vector2f(40.f, 40.f));
		rect.setPosition(pos);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(1.f);
	}

	sf::RectangleShape& getRect() {
		if (texNum != 0) {
			rect.setTexture(&tex);
			return rect;
		}

		rect.setFillColor(sf::Color::White);
		return rect;
	}
};

class EditorState : public State {
private:
	void initState();
	void loadTextures();
	sf::SoundBuffer buffer;
	sf::Sound music;
	std::vector<std::vector<MapTile>> tile;

	std::vector<Button> buttons;

	std::vector<MapTile> selection;

	int selected;

	sf::Sprite mouse;
	sf::Texture mouse_up, mouse_down;
public:
	EditorState();
	~EditorState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);
};

