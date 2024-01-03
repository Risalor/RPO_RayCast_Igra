#include "GamePlayState.h"

std::vector<Projectile*> GamePlayState::projectiles;
Player player(Player(10.0f));
void GamePlayState::initState() {
	
	enemy.push_back(new EnemyMelee(2, 3, 6, 5));
	enemy.push_back(new EnemyRange(6, 17, 7, 18));
	
	
	items.push_back(new Weapon(20, 15, 2, 10, 0.5, false,false, "pistol"));
	items.push_back(new Weapon(25, 15, 2, 10, 0.5, false,false, "AK-47"));
	items.push_back(new Weapon(25, 10, 2, 10, 0.5, false,false, "machinegun"));

	
	for (int i = 0;i < weapons.size();i++) {

		std::cout << "OROŽJE: " << weapons[i]->getName() << weapons[i]->getPickedStatus() <<  std::endl;
	}

	if (!buffer.loadFromFile("Assets/Music/GamePlay.wav")) {
		std::cout << "Faildes to load soundBuffer\n";
	}

	music.setBuffer(buffer);
	music.play();

	music.setLoop(true);
	music.setVolume(15.f);

	/*for (size_t i = 0;i < inv.getSize();i++) {
		std::cout << inv[i].debugPrint() << std::endl;
	}*/


}

void GamePlayState::initMap() {

	std::filesystem::path folder("Assets/Maps");

	if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
		for (const auto& it : std::filesystem::directory_iterator(folder)) {
			if (std::filesystem::is_regular_file(it)) {
				mapPaths.push_back(it.path().string());
			}
		}
	} else {
		std::cout << "Folder does not exist or is not a directory.\n";
	}

	std::fstream file(mapPaths.at(0), std::ios::in | std::ios::binary);

	glb::consts::worldMap.clear();

	int wid = 0, hei = 0;
	file.read(reinterpret_cast<char*>(&wid), sizeof(wid));
	file.read(reinterpret_cast<char*>(&hei), sizeof(hei));

	if (file.is_open()) {
		for (int i = 0; i < hei; i++) {
			glb::consts::worldMap.push_back(std::vector<int>());
			for (int j = 0; j < wid; j++) {
				int num = 0;
				file.read(reinterpret_cast<char*>(&num), sizeof(num));
				glb::consts::worldMap.at(i).push_back(num);
			}
		}
	}

	file.close();
}

void GamePlayState::playerMapRelation() {
	if (glb::consts::worldMap[int(player.getPos().x + player.getDir().x)][int(player.getPos().y + player.getDir().y)] > 6) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			std::fstream file(mapPaths.at(glb::consts::worldMap[int(player.getPos().x + player.getDir().x)][int(player.getPos().y + player.getDir().y)] - 7), std::ios::in | std::ios::binary);

			glb::consts::worldMap.clear();

			int wid = 0, hei = 0;
			file.read(reinterpret_cast<char*>(&wid), sizeof(wid));
			file.read(reinterpret_cast<char*>(&hei), sizeof(hei));

			if (file.is_open()) {
				for (int i = 0; i < hei; i++) {
					glb::consts::worldMap.push_back(std::vector<int>());
					for (int j = 0; j < wid; j++) {
						int num = 0;
						file.read(reinterpret_cast<char*>(&num), sizeof(num));
						glb::consts::worldMap.at(i).push_back(num);
					}
				}
			}

			file.close();
		}
	}
}

GamePlayState::GamePlayState() : State() {
	initMap();
	initState();
}

GamePlayState::~GamePlayState() {

	for (Item* item : items) {
        delete item;
    }
    items.clear();

}

void GamePlayState::update(float dt, sf::Vector2f mousePos) {
	player.update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		player.updateEquipment(items);
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.attack();
	}


	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->update(dt, player);
	}

	for (auto& projectile : projectiles) {
		projectile->update(dt, player);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		music.stop();
		music.resetBuffer();
		State::trigger = StateTrigger::END_STATE;
	}

	playerMapRelation();
}

void GamePlayState::addProjectile(Projectile* projectile) {
	projectiles.push_back(projectile);
}

void GamePlayState::removeProjectile(Projectile* projectile) {	
	for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
		if (*it == projectile) {
			
			projectiles.erase(it);			
			break;
		}
	}
}

void GamePlayState::draw(sf::RenderTarget* window) {

	map.draw(window, player, enemy, projectiles,items);
	player.renderHealthBar(window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		player.showInventory(window);
	}
}
