#pragma once
#include "State.h"
class GamePlayState : public State {
private:
	void initState();
	sf::CircleShape shape;
public:
	GamePlayState();
	~GamePlayState();
	void update(float dt);
	void draw(sf::RenderTarget* window);
};

