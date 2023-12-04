#pragma once
#include "State.h"
class GamePlayState : public State {
private:
	void initState();
	Player player;
	
	std::vector<Enemy*> enemy;
	Map map;

	sf::Sound music;
	sf::SoundBuffer buffer;
public:
	GamePlayState();
	~GamePlayState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);
};

