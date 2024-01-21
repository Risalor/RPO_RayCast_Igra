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
		rect.setFillColor(sf::Color::White);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(2.f);
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

struct MapFileDisplay {
	int id;
	std::string path;
	std::string file;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;

	MapFileDisplay(int id, std::string path, std::string file, sf::Vector2f poz) : id(id), path(path), file(file) {
		rect.setSize(sf::Vector2f(200.f, 20.f));
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(1.f);
		rect.setPosition(poz);

		if (!font.loadFromFile("Assets/Fonts/font1.otf")) {
			std::cout << "No font";
		}

		text.setCharacterSize(15.f);
		text.setString(file);
		text.setFont(font);
		text.setPosition(poz);
	}

	MapFileDisplay() {}

	void draw(sf::RenderTarget* window) {
		text.setFont(font);

		window->draw(rect);
		window->draw(text);
	}
};

struct LegendRow {
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;

	LegendRow(sf::Vector2f pos, std::string str) {
		rect.setSize(sf::Vector2f(200.f, 20.f));
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineColor(sf::Color::White);
		rect.setOutlineThickness(1.f);
		rect.setPosition(pos);

		if (!font.loadFromFile("Assets/Fonts/font1.ttf")) {
			std::cout << "No font";
		}

		text.setCharacterSize(15.f);
		text.setString(str);
		text.setFont(font);
		text.setPosition(pos);
	}

	LegendRow() {}

	void draw(sf::RenderTarget* window) {
		text.setFont(font);

		window->draw(rect);
		window->draw(text);
	}
};

//struct EnemyObj {
//	sf::Vector2f pos;
//	int type;
//	sf::CircleShape shp;
//
//	EnemyObj(sf::Vector2f pos, float rad, int type) : pos(pos), type(type) {
//		shp.setFillColor(sf::Color::Red);
//		shp.setOutlineColor(sf::Color::White);
//		shp.setOutlineThickness(1.f);
//		shp.setRadius(rad);
//		shp.setPosition(pos);
//	}
//
//	EnemyObj() {}
//};

struct EnemyObj {
	sf::Vector2f pos;
	int type;
	sf::Sprite shp;

	EnemyObj(sf::Vector2f pos, sf::Texture* texture, int type) : pos(pos), type(type) {
		shp.setTexture(*texture);
		shp.setScale(0.7f, 0.7f);
		shp.setPosition(pos);
	}

	EnemyObj() {}
};

struct PlayerObj {
	sf::Vector2f pos;
	sf::CircleShape shp;

	PlayerObj(sf::Vector2f pos, float rad) : pos(pos) {
		shp.setFillColor(sf::Color::Green);
		shp.setOutlineColor(sf::Color::White);
		shp.setOutlineThickness(1.f);
		shp.setRadius(rad);
		shp.setPosition(pos);
	}

	PlayerObj() {}
};

class EditorState : public State {
private:
	void initState();
	void loadTextures();
	void moveView();
	bool isMouseInView();
	sf::SoundBuffer buffer;
	sf::Sound music;
	std::vector<std::vector<MapTile>> tile;

	std::vector<Button> buttons;

	std::vector<MapTile> selection;

	int selected;

	sf::Sprite mouse;
	sf::Texture mouse_up, mouse_down;

	sf::View viewL, viewR;
	float zoom;
	sf::Vector2f worldCoords, mouseCoords;
	std::vector<MapFileDisplay> maps;
	MapFileDisplay selectedMap;

	float dtCounter;

	std::vector<EnemyObj> enemySelection;
	EnemyObj selectedEnemy;
	std::vector<EnemyObj> enemies;

	PlayerObj playerSelect;
	PlayerObj player;

	std::vector<LegendRow> legend;

	sf::Texture enemyTexture1;
public:
	EditorState();
	~EditorState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);
};

