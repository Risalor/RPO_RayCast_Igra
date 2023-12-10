#include "Decoration.h"

Decoration::Decoration() {

}

Decoration::~Decoration() {

	for (sf::Texture* decoTexture : decoTextures) {
		delete decoTexture;
	}

	for (sf::Sprite* decoSprite : decoSprites) {
		delete decoSprite;
	}
}

void Decoration::createDecoSprite(const int index) {

	sf::Texture* decoTexture = decoTextures[index];
	sf::Sprite* decoSprite = new sf::Sprite(*decoTexture);

	decoSprites.push_back(decoSprite);
}

void Decoration::addNewDecoTexture(const std::string& filePath) {
	sf::Texture* decoTexture = new sf::Texture();

	if (decoTexture->loadFromFile(filePath)) {
		decoTextures.push_back(decoTexture);
	}
	else {
		delete decoTexture;
		return;
	}
}

sf::Texture* Decoration::getDecoTexture(const int index) {
	return decoTextures[index];
}

sf::Sprite* Decoration::getDecoSprite(const int index) {
	return decoSprites[index];
}