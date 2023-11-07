#pragma once
#include <SFML/Graphics.hpp>

class Game {
private:
	sf::RenderWindow* window = nullptr;
	sf::CircleShape shape;
	void initWindow();
	void draw();
	void update();
public:
	Game();
	~Game();
	void run();
};

