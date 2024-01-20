#include "AnimationManager.h"

AnimationManager::AnimationManager(const int visisna, const int sirina, const int st_vrstic, const int st_stolpcev)
	: visina(visisna), sirina(sirina), st_vrstic(st_vrstic), st_stolpcev(st_stolpcev), visina_okvirja(visina / st_vrstic), sirina_okvirja(sirina / st_stolpcev)
{
}

AnimationManager::~AnimationManager() {

}

sf::IntRect AnimationManager::nextFrame(sf::IntRect rectSourceSprite, const int vrstica, const int stevilo, bool& premik) {
	bool prva = false;
	bool zadnja = false;

	if (stevilo == 1) {
		prva = true;
		zadnja = true;
	}
	else {
		// preverimo ali smo v prvi oz. zadnji vrstici
		if (trenutna_vrstica == vrstica) {
			prva = true;
		}
		if (trenutna_vrstica == vrstica + stevilo - 1) {
			zadnja = true;
		}
	}

	// nastavimo premik
	if (prva && rectSourceSprite.left == 0) {
		premik = true;
	}
	if (zadnja && rectSourceSprite.left == sirina_okvirja * (st_stolpcev - 1)) {
		premik = false;
	}

	// premik v desno
	if (premik) {
		// premik v novo vrstico
		if (rectSourceSprite.left == sirina_okvirja * (st_stolpcev - 1)) {
			rectSourceSprite.left = 0;
			rectSourceSprite.top += visina_okvirja;
			trenutna_vrstica++;
		}
		// premik v isti vrstici
		else {
			rectSourceSprite.left += sirina_okvirja;
		}
	}
	// premik v levo
	else {
		// premik v novo vrstico
		if (rectSourceSprite.left == 0) {
			rectSourceSprite.left = sirina_okvirja * (st_stolpcev - 1);
			rectSourceSprite.top -= visina_okvirja;
			trenutna_vrstica--;
		}
		// premik v isti vrstici
		else {
			rectSourceSprite.left -= sirina_okvirja;
		}
	}

	return rectSourceSprite;
}

sf::IntRect AnimationManager::getFrameByIndex(int index)
{
	int column = index % st_stolpcev;
	int row = index / st_stolpcev;
	return sf::IntRect(column * sirina_okvirja, row * visina_okvirja, sirina_okvirja, visina_okvirja);
}

sf::Sprite* AnimationManager::createAnimation(sf::Texture* texture, const int vrstica, const int stevilo) {
	sf::Texture* spriteSheet = texture;

	sf::IntRect rectSourceSprite(0, visina_okvirja * (vrstica - 1), sirina_okvirja, visina_okvirja);
	sf::Sprite* sprite = new sf::Sprite(*spriteSheet, rectSourceSprite);

	trenutna_vrstica = vrstica;
	bool premik = true; // premik v desno

	// rectSourceSprite = nextFrame(rectSourceSprite, vrstica, stevilo, premik);

	sprite->setTextureRect(rectSourceSprite);

	return sprite;
}

/*
void AnimationManager::deleteAnimation(sf::Animation* Animation) {

	auto AnimationIter = std::find(Animations.begin(), Animations.end(), Animation);

	if (AnimationIter != Animations.end()) {
		int index = std::distance(Animations.begin(), AnimationIter);

		delete Animations[index];
		delete textures[index];

		Animations.erase(AnimationIter);
		textures.erase(textures.begin() + index);
	}
}
*/


/*
sf::Animation* AnimationManager::getAnimation(const int index) {
	return Animations[index];
}
*/