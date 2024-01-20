#include "GamePlayState.h"

const float PI = 3.14159265358979323846f;

Player player(Player(10.0f));
std::vector<Projectile*> GamePlayState::projectiles;
std::vector<Enemy*> GamePlayState::enemies;
sf::Clock attackTimer;
sf::Clock shootingAnimationTimer;
void GamePlayState::initState() {

	//289, 291
	items.push_back(new Weapon(20, 15, 5, 10, 0.5, false, false, false, "pistol1", 200, 200, 2, 2));
	items.push_back(new Weapon(25, 15, 10, 10, 1, false, false, false, "shotgun", 200, 200, 2, 2));
	items.push_back(new Weapon(25, 10, 2, 10, 0.2, false, false, false, "machinegun", 470, 300, 2, 2));
	
	this->isShooting = false;

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

	std::fstream file("Assets/conf.bin", std::ios::in | std::ios::binary);
	int temp;
	file.read(reinterpret_cast<char*>(&temp), sizeof(int));
	file.close();

	music.setVolume(temp);

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

	for (Enemy* e : enemies) {
		delete e;
	}
	enemies.clear();

	for (Projectile* p : projectiles) {
		delete p;
	}
	projectiles.clear();

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
		attack();
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		isShooting = false;
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
	for (auto it = projectiles.begin(); it != projectiles.end(); ) {
		if (*it == projectile) {
			it = projectiles.erase(it);
		}
		else {
			++it;
		}
	}
}

void GamePlayState::removeEnemy(Enemy* enemy) {
	for (auto it = enemies.begin(); it != enemies.end(); ) {
		if (*it == enemy) {
			it = enemies.erase(it);
		}
		else {
			++it;
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
		drawWeapons(window);
	}
	
}

void GamePlayState::normalizeVector(sf::Vector2f& vector) {
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length != 0) {
		vector.x /= length;
		vector.y /= length;
	}
}

bool GamePlayState::lineOfSightToEnemy(const sf::Vector2f& playerPos, const sf::Vector2f& enemyPos) {
	sf::Vector2f direction = enemyPos - playerPos;
	normalizeVector(direction);

	float distance = calculateDistance(playerPos, enemyPos);
	float stepSize = 1.0f; // Nastavi korak, s katerim se premika po liniji

	// Preveri vsako točko na liniji od igralca do sovražnika
	for (float t = 0.0f; t < distance; t += stepSize) {
		sf::Vector2f currentPoint = playerPos + direction * t;
		if (glb::consts::worldMap[int(currentPoint.x)][int(currentPoint.y)]) {
			// Našli smo steno, ni vidne linije do sovražnika
			return false;
		}
	}

	// Ni sten na poti do sovražnika, igralec ima vidno linijo
	return true;
}

void GamePlayState::drawWeapons(sf::RenderTarget* window)
{

	Weapon* weapon = player.getItem();
	
	if (weapon != nullptr) {
		std::string textureName = weapon->getName();
		std::string fullPath = "Assets/Weapons/" + textureName + ".png";
		sf::Texture weaponTexture;
		if (!weaponTexture.loadFromFile(fullPath)) {
			std::cout << "Napaka pri odpiranju!" << std::endl;
		}
		AnimationManager animManager(
			weapon->getSpriteSheetWidth(),
			weapon->getSpriteSheetHeight(),
			weapon->getNumFramesVertical(),
			weapon->getNumFramesHorizontal()
		);

		sf::Sprite weaponSprite;
		weaponSprite.setTexture(weaponTexture);
		weaponSprite.setPosition(450, 280); 
		float scaleX = 0;
		float scaleY = 0;
		if(weapon->getName() == "machinegun"){
			weaponSprite.setPosition(250, 355);
			 scaleX = 580 / weapon->getSpriteSheetWidth();
			 scaleY = 580 / weapon->getSpriteSheetHeight();
		}
		else {
			 scaleX = 500 / weapon->getSpriteSheetWidth();
			 scaleY = 500 / weapon->getSpriteSheetHeight();
		}
			
		weaponSprite.setScale(scaleX, scaleY);


		if (isShootingAnimation) {
			if (shootingAnimationTimer.getElapsedTime().asSeconds() < shootingAnimationDuration) {
				weaponSprite.setTextureRect(animManager.getFrameByIndex(1)); // Drugi okvir med animacijo streljanja
			}
			else {
				isShootingAnimation = false;
			}
		}
		if (!isShootingAnimation) {
			weaponSprite.setTextureRect(animManager.getFrameByIndex(0)); // Nazaj na prvi okvir
		}
		window->draw(weaponSprite);
	}
}




void GamePlayState::attack()
{
	
	if (player.inventoryEmpty()) {
		
			isShooting = true;
		Weapon* weapon = player.getItem();

		if (attackTimer.getElapsedTime().asSeconds() >= weapon->getCoolDown()) {
			isShootingAnimation = true;
			shootingAnimationTimer.restart();
			attackTimer.restart();
		for (auto& enemy : enemies) {
			float distanceToEnemy = calculateDistance(player.getPos(), enemy->getPos());
			if (distanceToEnemy <= weapon->getRange()) {


				sf::Vector2f directionToEnemy = enemy->getPos() - player.getPos();
				normalizeVector(directionToEnemy);

				float dotProduct = player.getDir().x * directionToEnemy.x + player.getDir().y * directionToEnemy.y;
				float angle = std::acos(dotProduct) * 180.0f / PI; // Pretvorba v stopinje

				if (angle < 20.0f) { // Možna napaka 20 stopinj
					
						if (lineOfSightToEnemy(player.getPos(), enemy->getPos())) { // Preverimo, ali je vidna linija
						float distanceToEnemy = calculateDistance(player.getPos(), enemy->getPos());
						if (distanceToEnemy <= weapon->getRange()) {
							enemy->takeDamage(weapon->getDamage());
							std::cout << "SOVRAZNIK ZADET, oddaljenost: " << distanceToEnemy << std::endl;
						}
						}
						else {
							std::cout << "Napad blokiran s steno" << std::endl;
						}
						
					}
				}
			}
		}
	}
	else {
		std::cout << "Inventory empty!" << std::endl;
	}
	
}