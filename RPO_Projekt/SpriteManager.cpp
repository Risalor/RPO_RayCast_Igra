#include "SpriteManager.h"

SpriteManager::SpriteManager() {

}

// destruktor --> odstrani vse sprite in teksture
SpriteManager::~SpriteManager() {

	for (sf::Texture* texture : textures) {
		delete texture;
	}

	for (sf::Sprite* sprite : sprites) {
		delete sprite;
	}

}

void SpriteManager::createSprite(const int index) {

	sf::Texture* texture = textures[index];
	sf::Sprite* sprite = new sf::Sprite(*texture);

	sprites.push_back(sprite);
}

/*
void SpriteManager::deleteSpriteInfo(struct sprite_info spriteInfo) {

	auto spriteIter = std::find(sprites.begin(), sprites.end(), spriteInfo);

	if (spriteIter != sprites.end()) {
		int index = std::distance(sprites.begin(), spriteIter);

		delete sprites[index].sprite;

		sprites.erase(spriteIter);
	}
}
*/

// vrne nullptr, ce pride do napake pri nalaganju teksture
void SpriteManager::addNewTexture(const std::string& filePath) {

	sf::Texture* texture = new sf::Texture();

	if (texture->loadFromFile(filePath)) {
		textures.push_back(texture);
	}
	else {
		delete texture;
		return;
	}
}

sf::Texture* SpriteManager::getTexture(const int index) {
	return textures[index];
}

sf::Sprite* SpriteManager::getSprite(const int index) {
	return sprites[index];
}