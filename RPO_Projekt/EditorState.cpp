#include "EditorState.h"

void EditorState::initState() {
	for (int i = 0; i < 200; i++) {
		tile.push_back(std::vector<MapTile>());
		for (int j = 0; j < 200; j++) {
			tile.at(tile.size() - 1).push_back(MapTile(0, sf::Vector2f(17.f * j, 17.f * i)));
		}
	}

	if (!buffer.loadFromFile("Assets/Music/EditorState.wav")) {
		std::cout << "Faildes to load soundBuffer\n";
	}

	music.setBuffer(buffer);
	music.play();

	music.setLoop(true);
	music.setVolume(25.f);

	if (!mouse_up.loadFromFile("Assets/Cursor/cursor.gif")) {
		std::cout << "Cannot load texture\n";
	}

	if (!mouse_down.loadFromFile("Assets/Cursor/cursor_down.gif")) {
		std::cout << "Cannot load texture\n";
	}

	buttons.push_back(Button(sf::Vector2f(453.f, 50.f), "Clear"));
	buttons.push_back(Button(sf::Vector2f(453.f, 0.f), "Save"));
	buttons.push_back(Button(sf::Vector2f(453.f, 100.f), "Load"));
	buttons.push_back(Button(sf::Vector2f(453.f, 150.f), "New"));
	buttons.push_back(Button(sf::Vector2f(453.f, 200.f), "Delete"));
	
	for (auto& it : buttons) {
		it.setScale(0.5f);
	}

	viewL = sf::View(sf::FloatRect(0, 0, 411, screenHeight));
	viewR = sf::View(sf::FloatRect(411, 0, screenWidth, screenHeight));

	viewL.setViewport(sf::FloatRect(0.f, 0.f, 0.36f, 1.f));
	viewR.setViewport(sf::FloatRect(0.36f, 0.f, 0.64f, 1.f));
	viewL.setSize(100, 117);
	zoom = 1.f;

	std::filesystem::path folder("Assets/Maps");
	int offset = 0;

	if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
		for (const auto& it : std::filesystem::directory_iterator(folder)) {
			if (std::filesystem::is_regular_file(it)) {
				maps.push_back(MapFileDisplay(offset + 1, "Assets/Maps", it.path().filename().string(), sf::Vector2f(600.f, 10.f + 25.f * offset)));
				offset++;
			}
		}
	} else {
		std::cout << "Folder does not exist or is not a directory.\n";
	}

	dtCounter = 0;
}

void EditorState::loadTextures() {
	std::filesystem::path folder("Assets/WallTex");
	int offset = 1;
	sf::Texture texture;
	selection.push_back(MapTile(0, sf::Vector2f(413, 1), texture));
	if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
		for (const auto& it : std::filesystem::directory_iterator(folder)) {
			if (std::filesystem::is_regular_file(it)) {
				if (!texture.loadFromFile(it.path().string())) {
					std::cout << "Cannot load texture\n";
				}

				selection.push_back(MapTile(selection.size(), sf::Vector2f(413, 40 * offset + 1), texture));
				offset++;
			}
		}
	} else {
		std::cout << "Folder does not exist or is not a directory.\n";
	}

	enemySelection.push_back(EnemyObj(sf::Vector2f(413.f, 40 * offset + 3), 20, 1));
	enemySelection.push_back(EnemyObj(sf::Vector2f(413.f, 40 * (offset + 1) + 5), 20, 2));
}

void EditorState::moveView() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		zoom *= 0.9f;
		viewL.setSize(100 * zoom, 117 * zoom);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		zoom *= 1.1f;
		viewL.setSize(100 * zoom, 117 * zoom);
	}

	if (zoom > 10.f) {
		zoom = 10.f;
	}

	if (zoom < 0.5f) {
		zoom = 0.5f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		viewL.move(-2.f * zoom, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		viewL.move(2.f * zoom, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		viewL.move(0.f, -2.f * zoom);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		viewL.move(0.f, 2.f * zoom);
	}
}

bool EditorState::isMouseInView() {
	sf::FloatRect viewBounds(
		viewL.getCenter().x - viewL.getSize().x / 2.f,
		viewL.getCenter().y - viewL.getSize().y / 2.f,
		viewL.getSize().x,
		viewL.getSize().y
	);

	return viewBounds.contains(worldCoords);
}



EditorState::EditorState() {
	initState();
	loadTextures();
}

EditorState::~EditorState() {

}

void EditorState::update(float dt, sf::Vector2f mousePos) {
	mouse.setPosition(mousePos);
	mouseCoords = mousePos;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouse.setTexture(mouse_down);
	} else {
		mouse.setTexture(mouse_up);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		music.stop();
		music.resetBuffer();
		State::trigger = StateTrigger::END_STATE;
	}

	buttons.at(0).update(mousePos);
	buttons.at(1).update(mousePos);
	buttons.at(2).update(mousePos);
	buttons.at(3).update(mousePos);
	buttons.at(4).update(mousePos);

	moveView();

	if (buttons.at(0).clicked()) {
		for (auto& it : tile) {
			for (auto& it2 : it) {
				it2.rect.setTexture(nullptr);
				it2.texNum = 0;
			}
		}

		enemies.clear();
	}

	if (buttons.at(1).clicked()) {

		int wid = 0, hei = 0;

		for (auto& it : tile.at(0)) {
			if (it.texNum != 0) {
				wid++;
			} else {
				break;
			}
		}

		for (auto& it : tile) {
			if (it.at(0).texNum != 0) {
				hei++;
			} else {
				break;
			}
		}

		std::fstream file(selectedMap.path + "/" + selectedMap.file, std::ios::out | std::ios::binary);

		file.write(reinterpret_cast<const char*>(&wid), sizeof(int));
		file.write(reinterpret_cast<const char*>(&hei), sizeof(int));

		for (int i = 0; i < hei; i++) {
			for (int j = 0; j < wid; j++) {
				file.write(reinterpret_cast<const char*>(&tile[i][j].texNum), sizeof(int));
			}
			std::cout << "\n";
		}

		int size = enemies.size();
		file.write(reinterpret_cast<const char*>(&size), sizeof(int));

		for (auto& it : enemies) {
			double temp = it.pos.x / 17.f;
			file.write(reinterpret_cast<const char*>(&temp), sizeof(double));
			double temp2 = it.pos.y / 17.f;
			file.write(reinterpret_cast<const char*>(&temp2), sizeof(double));
			file.write(reinterpret_cast<const char*>(&it.type), sizeof(int));
		}

		file.close();
	}

	if (buttons.at(2).clicked()) {
		int wid = 0, hei = 0;

		for (auto& it : tile) {
			for (auto& it2 : it) {
				it2.rect.setTexture(nullptr);
				it2.texNum = 0;
			}
		}

		std::fstream file(selectedMap.path + "/" + selectedMap.file, std::ios::in | std::ios::binary);

		file.read(reinterpret_cast<char*>(&wid), sizeof(wid));
		file.read(reinterpret_cast<char*>(&hei), sizeof(hei));

		if (file.is_open()) {
			for (int i = 0; i < hei; i++) {
				for (int j = 0; j < wid; j++) {
					int num = 0;
					file.read(reinterpret_cast<char*>(&num), sizeof(num));
					if (num < 7) {
						tile.at(i).at(j).texNum = num;
						tile.at(i).at(j).tex = selection.at(num).tex;
					} else {
						tile.at(i).at(j).texNum = num;
						tile.at(i).at(j).tex = selection.at(5).tex;
					}
				}
			}
		}

		int size, type;
		double pozX, pozY;
		file.read(reinterpret_cast<char*>(&size), sizeof(int));
		
		for (int i = 0; i < size; i++) {
			file.read(reinterpret_cast<char*>(&pozX), sizeof(double));
			file.read(reinterpret_cast<char*>(&pozY), sizeof(double));
			file.read(reinterpret_cast<char*>(&type), sizeof(int));
			enemies.push_back(EnemyObj(sf::Vector2f(pozX * 17.f, pozY * 17.f), 5.f, type));
		}

		file.close();
	}

	dtCounter += dt;

	if (buttons.at(3).clicked() && dtCounter > 1.f) {
		maps.push_back(MapFileDisplay(maps.size() + 1, "Assets/Maps", "MapLay" + std::to_string(maps.size() + 1) + ".ors", sf::Vector2f(800.f, 100.f + 25.f * maps.size())));
		dtCounter = 0.f;
	}

	if (buttons.at(4).clicked() && dtCounter > 1.f) {
		std::remove((selectedMap.path + "/" + selectedMap.file).c_str());
		maps.erase(maps.begin() + selectedMap.id - 1);
		dtCounter = 0;
	}

	for (auto& it : selection) {
		if (it.rect.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			selected = it.texNum;
		}

		if (selected == it.texNum) {
			it.rect.setOutlineColor(sf::Color::Green);
		} else {
			it.rect.setOutlineColor(sf::Color::White);
		}
	}

	for (auto& it : enemySelection) {
		if (it.shp.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			selectedEnemy = it;
			it.shp.setOutlineColor(sf::Color::Green);
			selected = 0;
		}

		if (it.type != selectedEnemy.type) {
			it.shp.setOutlineColor(sf::Color::White);
		}

		if (selected != 0) {
			it.shp.setOutlineColor(sf::Color::White);
			selectedEnemy.type = 0;
		}
	}

	if (isMouseInView() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && dtCounter > 0.5f && selectedEnemy.type != 0) {
		enemies.push_back(EnemyObj(worldCoords, 5.f, selectedEnemy.type));
		dtCounter = 0.f;
	}

	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].shp.getGlobalBounds().contains(worldCoords) && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			enemies.erase(enemies.begin() + i);
		}
	}

	for (auto& it : maps) {
		if (it.rect.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			selectedMap = it;
			selected = it.id + 6;
		}

		if (selectedMap.file == it.file) {
			it.rect.setOutlineColor(sf::Color::Green);
		} else {
			it.rect.setOutlineColor(sf::Color::White);
		}
	}

	for (auto& it : tile) {
		for (auto& it2 : it) {
			if (it2.rect.getGlobalBounds().contains(sf::Vector2f(worldCoords)) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseInView()) {
				it2.texNum = selected;
				if (selected != 0 && selected < 7) {
					it2.tex = selection.at(selected).tex;
				} else if (selected > 6) {
					it2.tex = selection.at(5).tex;
				} else if (selected == 0) {
					it2.rect.setTexture(nullptr);
				}
			}
		}
	}
}

void EditorState::draw(sf::RenderTarget* window) {

	window->setView(viewL);

	sf::Vector2f topLeft = window->mapPixelToCoords(sf::Vector2i(0, 0));
	sf::Vector2f bottomRight = window->mapPixelToCoords(sf::Vector2i(411, 480));

	int leftTile = static_cast<int>(topLeft.x / 17);
	int rightTile = static_cast<int>(bottomRight.x / 17);
	int topTile = static_cast<int>(topLeft.y / 17);
	int bottomTile = static_cast<int>(bottomRight.y / 17);

	// Draw only the visible tiles
	for (int i = std::max(0, topTile); i <= std::min(200 - 1, bottomTile); i++) {
		for (int j = std::max(0, leftTile); j <= std::min(200 - 1, rightTile); j++) {
			window->draw(tile[i][j].getRect());
		}
	}

	for (auto& it : enemies) {
		window->draw(it.shp);
	}

	worldCoords = window->mapPixelToCoords(sf::Vector2i(mouseCoords));

	window->setView(viewR);

	for (auto& it : selection) {
		window->draw(it.getRect());
	}

	window->draw(enemySelection.at(0).shp);
	window->draw(enemySelection.at(1).shp);

	for (auto& it : buttons) {
		it.draw(window);
	}

	for (auto& it : maps) {
		it.draw(window);
	}

	window->setView(window->getDefaultView());

	window->draw(mouse);
}
