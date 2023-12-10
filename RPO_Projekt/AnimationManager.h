#pragma once
#include <SFML/Graphics.hpp>
#include "global.h"
#include "SpriteManager.h"

class AnimationManager {
public:
	AnimationManager(const int visina, const int sirina, const int st_vrstic, const int st_stolpcev);

	~AnimationManager();

	sf::Sprite* createAnimation(sf::Texture* texture, const int vrstica, const int st);

	sf::IntRect nextFrame(sf::IntRect rectSourceSprite, const int vrstica, const int stevilo, bool& premik);

	//void delete Animation(sf::Sprite* spriteSheet);
	//sf::Animation* getAnimation(const int index);


private:
	const int visina;
	const int sirina;
	const int st_vrstic;
	const int st_stolpcev;

	const float visina_okvirja;
	const float sirina_okvirja;
	int trenutna_vrstica = 0;
};