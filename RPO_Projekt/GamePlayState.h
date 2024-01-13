#pragma once
#include "State.h"

struct GameOverBanner {
	sf::RectangleShape shp;
	sf::Texture tex;
	Button restart;

	GameOverBanner() {
		restart = Button(sf::Vector2f(screenWidth / 2 + 100, screenHeight / 2), "Restart");
		if (!tex.loadFromFile("Assets/Backgrounds/gameover.png")) {
			std::cout << "File cannot be loaded";
		}
		shp.setSize(sf::Vector2f(screenHeight, screenHeight));
		shp.setPosition((screenWidth)/2 - 20, 0.f);
		shp.setTexture(&tex);
	}

	void draw(sf::RenderTarget* window) {
		window->draw(shp);
		restart.draw(window);
	}
};

class GamePlayState : public State {
private:
	void initState();
	void initMap();
	void playerMapRelation();
	void playerDead();


	std::vector<Weapon*> weapons;
	std::vector<Item*> items;
	static std::vector<Enemy*> enemies;
	static std::vector<Projectile*> projectiles;

	bool playerDeadVar;
	bool stageCleared;
	GameOverBanner gameOver;

	sf::Sprite mouse;
	sf::Texture mouse_up, mouse_down;

	Map map;

	sf::Sound music;
	sf::SoundBuffer buffer;
	std::vector<std::string> mapPaths;
public:
	GamePlayState();
	~GamePlayState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);

	static void addProjectile(Projectile* projectile);
	static void removeProjectile(Projectile* projectile);
	static void removeEnemy(Enemy* enemy);

	float calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	void normalizeVector(sf::Vector2f& vector);
};

