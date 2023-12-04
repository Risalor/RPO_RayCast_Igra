#pragma once
#include "GamePlayState.h"

class EditorState : public State {
private:
	void initState();
public:
	EditorState();
	~EditorState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);
};

