#include "GamePlayState.h"

const float PI = 3.14159265358979323846f;

Player player(Player(10.0f));
std::vector<Projectile*> GamePlayState::projectiles;
std::vector<Enemy*> GamePlayState::enemies;

void GamePlayState::initState() {


	items.push_back(new Weapon(20, 15, 2, 10, 0.5, false, false, false, "pistol"));
	items.push_back(new Weapon(25, 15, 2, 10, 0.5, false, false, false, "AK-47"));
	items.push_back(new Weapon(25, 10, 2, 10, 0.5, false, false, false, "machinegun"));


	if (!buffer.loadFromFile("Assets/Music/GamePlay.wav")) {
		std::cout << "Faildes to load soundBuffer\n";
	}

	if (!vicBuffer.loadFromFile("Assets/Music/victory.wav")) {
		std::cout << "Faildes to load soundBuffer\n";
	}

	if (!deaBuffer.loadFromFile("Assets/Music/death.wav")) {
		std::cout << "Faildes to load soundBuffer\n";
	}

	vicMusic.setBuffer(vicBuffer);
	deaMusic.setBuffer(deaBuffer);
	vicPlayedOnce = false;
	deaPlayedOnce = false;

	music.setBuffer(buffer);
	music.play();

	music.setLoop(true);
	music.setVolume(15.f);

	playerDeadVar = false;
	stageCleared = false;

	if (!mouse_up.loadFromFile("Assets/Cursor/cursor.gif")) {
		std::cout << "Cannot load texture\n";
	}

	if (!mouse_down.loadFromFile("Assets/Cursor/cursor_down.gif")) {
		std::cout << "Cannot load texture\n";
	}

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
	}
	else {
		std::cout << "Folder does not exist or is not a directory.\n";
	}

	currentMapNum = 0;

	loadmap(currentMapNum);
}

void GamePlayState::playerMapRelation() {
	if (glb::consts::worldMap[int(player.getPos().x + player.getDir().x)][int(player.getPos().y + player.getDir().y)] > 6 && stageCleared) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			stageCleared = false;
			stageClearedB.usedOnce = false;
			vicPlayedOnce = false;
			currentMapNum = glb::consts::worldMap[int(player.getPos().x + player.getDir().x)][int(player.getPos().y + player.getDir().y)] - 7;
			loadmap(currentMapNum);
		}
	}
}

//Funkcija ki preverja če je player umrl
void GamePlayState::playerDead() {
	if (player.getHp() < 1) {
		playerDeadVar = true;
	}
}

void GamePlayState::loadmap(int mapNum) {
	std::fstream file(mapPaths.at(mapNum), std::ios::in | std::ios::binary);

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

		//Memory leaks, memory leaks everywhere
		/*for (auto& it : enemies) {
			delete it;
		}*/

		enemies.clear();

		int size;
		file.read(reinterpret_cast<char*>(&size), sizeof(size));

		for (int i = 0; i < size; i++) {
			int type;
			double x, y;
			file.read(reinterpret_cast<char*>(&y), sizeof(y));
			file.read(reinterpret_cast<char*>(&x), sizeof(x));
			file.read(reinterpret_cast<char*>(&type), sizeof(type));

			if (type == 1) {
				enemies.push_back(new EnemyMelee(int(x), int(y), int(x) - 1, int(y) - 1));
			}
			else {
				enemies.push_back(new EnemyRange(int(x), int(y), int(x) - 1, int(y) - 1));
			}
		}
	}

	file.close();
}

void GamePlayState::mouseUpdate(sf::Vector2f mousePos) {
	mouse.setPosition(mousePos);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouse.setTexture(mouse_down);
	}
	else {
		mouse.setTexture(mouse_up);
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
	if (playerDeadVar) {
		mouseUpdate(mousePos);
		gameOver.button.update(mousePos);
		gameOver.button2.update(mousePos);
		if (!deaPlayedOnce) {
			music.stop();
			deaMusic.play();
			deaPlayedOnce = true;
		}
	}

	if (stageCleared) {
		mouseUpdate(mousePos);
		stageClearedB.button.update(mousePos);
		if (!vicPlayedOnce) {
			music.stop();
			vicMusic.play();
			vicPlayedOnce = true;
		}
	}

	playerDead();
	player.update(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		player.updateEquipment(items);
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //tukaj izvajanje napadanja, ker v player razredu to ni mogoče-> če Player razred includan v Enemy in Enemy v Player-> ne deluje

		if (player.inventoryEmpty()) {

			Weapon weapon = player.getItem();


			for (auto& enemy : enemies) {
				float distanceToEnemy = calculateDistance(player.getPos(), enemy->getPos());
				if (distanceToEnemy <= weapon.getRange()) {


					sf::Vector2f directionToEnemy = enemy->getPos() - player.getPos();
					normalizeVector(directionToEnemy);

					float dotProduct = player.getDir().x * directionToEnemy.x + player.getDir().y * directionToEnemy.y;
					float angle = std::acos(dotProduct) * 180.0f / PI; // Pretvorba v stopinje

					if (angle < 20.0f) { // Možna napaka 20 stopinj
						float distanceToEnemy = calculateDistance(player.getPos(), enemy->getPos());
						if (distanceToEnemy <= weapon.getRange()) {
							enemy->takeDamage(1);
							std::cout << "SOVRAZNIK ZADET, oddaljenost: " << distanceToEnemy << std::endl;
						}
					}
				}
			}
		} else {
			std::cout << "Inventory empty!" << std::endl;
		}
	}

	//Spremenjivka s katero preverimo če lahko igralec gre v naslednjo mapo. Lahko gre ko so vsi sovražniki premagani.
	if (enemies.empty()) {
		stageCleared = true;
	}


	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(dt, player);
	}

	for (auto& projectile : projectiles) {
		projectile->update(dt, player);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		music.stop();
		music.resetBuffer();
		State::trigger = StateTrigger::END_STATE;
	}

	//V tem if stavku se more vse resetirati po tem ko se restart klikne
	if (playerDeadVar) {
		if (gameOver.button.clicked()) {
			music.play();
			deaPlayedOnce = false;
			playerDeadVar = false;
			player.setHp(10);
			loadmap(currentMapNum);
		}

		if (gameOver.button2.clicked()) {
			player.setHp(10);
			music.stop();
			music.resetBuffer();
			State::trigger = StateTrigger::END_STATE;
		}
	}

	if (stageCleared && stageClearedB.button.clicked()) {
		stageClearedB.usedOnce = true;
		music.play();

		if (currentMapNum == 2) {
			music.stop();
			music.resetBuffer();
			State::trigger = StateTrigger::END_STATE;
		}
	}

	playerMapRelation();
}

void GamePlayState::addProjectile(Projectile* projectile) {
	projectiles.push_back(projectile);
}

void GamePlayState::removeProjectile(Projectile* projectile) {
	//Memory leaks, memory leaks everywhere
	for (auto it = projectiles.begin(); it != projectiles.end(); ++it) {
		if (*it == projectile) {

			projectiles.erase(it);
			break;
		}
	}
}

void GamePlayState::removeEnemy(Enemy* enemy) {
	//Memory leaks, memory leaks everywhere
	for (auto it = enemies.begin(); it != enemies.end(); ++it) {
		if (*it == enemy) {

			enemies.erase(it);
			break;
		}
	}
}


float GamePlayState::calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {
	sf::Vector2f diff = pos1 - pos2;
	return std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

void GamePlayState::draw(sf::RenderTarget* window) {

	if (playerDeadVar) {//Če player živi se vse izrisuje če pa ne živi pa se nič ne izrisuje.
		gameOver.draw(window);
		window->draw(mouse);
	} else if (stageCleared && !stageClearedB.usedOnce) {
		stageClearedB.draw(window);
		window->draw(mouse);
	} else {
		map.draw(window, player, enemies, projectiles, items);
		player.renderHealthBar(window);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			player.showInventory(window);
		}
	}
}

void GamePlayState::normalizeVector(sf::Vector2f& vector) {
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length != 0) {
		vector.x /= length;
		vector.y /= length;
	}
}