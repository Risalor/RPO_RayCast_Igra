#pragma once
#include "State.h"
class GamePlayState : public State {
private:
	void initState();
	Player player;
	Map map;
public:
	GamePlayState();
	~GamePlayState();
	void update(float dt);
	void draw(sf::RenderTarget* window);
};

