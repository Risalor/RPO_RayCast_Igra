#pragma once
#include "State.h"

struct GameOverBanner {
	sf::RectangleShape shp;
	sf::Texture tex;
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

