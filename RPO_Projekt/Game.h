#pragma once
#include "GamePlayState.h"
#include <stack>

class Game {
private:
	sf::RenderWindow* window = nullptr;
	std::stack<State*> states;
	float deltaTime;
	void initWindow();
	void draw();
	void update();
public:
	Game();
	~Game();
	void run();
};

