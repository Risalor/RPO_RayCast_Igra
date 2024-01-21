#pragma once
#include "State.h"

struct GameOverBanner {
	sf::RectangleShape shp;
	sf::Texture tex;
	Button button;
	Button button2;

	GameOverBanner() {
		button = Button(sf::Vector2f(240.f, screenHeight / 2), "Restart");
		button2 = Button(sf::Vector2f(240.f, screenHeight / 2 + 100), "Title screen");
		if (!tex.loadFromFile("Assets/Backgrounds/gameover.png")) {
			std::cout << "File cannot be loaded";
		}
		shp.setSize(sf::Vector2f(screenHeight, screenHeight));
		shp.setPosition(120.f, 0.f);
		shp.setTexture(&tex);
	}

	void draw(sf::RenderTarget* window) {
		window->draw(shp);
		button.draw(window);
		button2.draw(window);
	}
};

struct StageClearedBanner {
	sf::RectangleShape shp;
	sf::Texture tex;
	Button button;
	bool usedOnce;

	StageClearedBanner() {
		button = Button(sf::Vector2f(270, screenHeight / 2 + 100), "Close");
		if (!tex.loadFromFile("Assets/Backgrounds/victory.png")) {
			std::cout << "File cannot be loaded";
		}

		shp.setSize(sf::Vector2f(screenHeight + 300, screenHeight));
		/*shp.setPosition((screenWidth) / 2 - 170, 0.f);*/
		shp.setPosition(0, 0.f);
		shp.setTexture(&tex);

		usedOnce = false;
	}

	void draw(sf::RenderTarget* window) {
		window->draw(shp);
		button.draw(window);
	}
};

class GamePlayState : public State {
private:
	void initState();
	void initMap();
	void playerMapRelation();
	void playerDead();
	void loadmap(int mapNum);
	void mouseUpdate(sf::Vector2f mousePos);

	std::vector<Weapon*> weapons;
	std::vector<Item*> items;
	static std::vector<Enemy*> enemies;
	static std::vector<Projectile*> projectiles;

	bool playerDeadVar;
	bool stageCleared;
	GameOverBanner gameOver;
	StageClearedBanner stageClearedB;

	sf::Sprite mouse;
	sf::Texture mouse_up, mouse_down;

	Map map;
	int currentMapNum;

	sf::Sound music, vicMusic, deaMusic;
	sf::SoundBuffer buffer, vicBuffer, deaBuffer;
	bool vicPlayedOnce;
	bool deaPlayedOnce;
	std::vector<std::string> mapPaths;
	bool isShooting;
	const float shootingAnimationDuration = 0.2f;
	bool isShootingAnimation = false;
public:
	GamePlayState();
	~GamePlayState();
	void update(float dt, sf::Vector2f mousePos);
	void draw(sf::RenderTarget* window);

	static void addProjectile(Projectile* projectile);
	static void removeProjectile(Projectile* projectile);
	static void removeEnemy(Enemy* enemy);

	void attack();
	float calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
	void normalizeVector(sf::Vector2f& vector);
	bool lineOfSightToEnemy(const sf::Vector2f& playerPos, const sf::Vector2f& enemyPos);
	void drawWeapons(sf::RenderTarget* window);
};

