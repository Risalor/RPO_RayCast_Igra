#pragma once
#include "State.h"
class GamePlayState : public State {
private:
	void initState();
	Player player;
	sf::CircleShape shape;
	Map map;
public:
	GamePlayState();
	~GamePlayState();
	void update(float dt);
	void draw(sf::RenderTarget* window);
};

