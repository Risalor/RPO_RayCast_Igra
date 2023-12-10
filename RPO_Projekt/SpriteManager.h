#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"
#include <vector>

class SpriteManager {
public:
	SpriteManager();
	~SpriteManager();

	void createSprite(const int index);
	// void deleteSpriteInfo(struct sprite_info spriteInfo);

	void addNewTexture(const std::string& filePath);
	sf::Texture* getTexture(const int index);
	sf::Sprite* getSprite(const int index);

private:
	std::vector<sf::Texture*> textures;
	std::vector<sf::Sprite*> sprites;
};
