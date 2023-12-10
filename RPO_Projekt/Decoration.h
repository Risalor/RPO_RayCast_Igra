#pragma once
#include "SpriteManager.h"

class Decoration {
public:
	Decoration();
	~Decoration();

	void createDecoSprite(const int index);
	void addNewDecoTexture(const std::string& filePath);
	sf::Texture* getDecoTexture(const int index);
	sf::Sprite* getDecoSprite(const int index);

private:
	std::vector<sf::Texture*> decoTextures;
	std::vector<sf::Sprite*> decoSprites;
};