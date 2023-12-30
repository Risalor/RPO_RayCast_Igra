#pragma once
#include "State.h"
class GamePlayState : public State {
private:
	void initState();
	void initMap();
	void playerMapRelation();
	Player player;

	std::vector<Enemy*> enemy;
	static std::vector<Projectile*> projectiles;
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
};

