#include "EditorState.h"

void EditorState::initState() {
	for (int i = 0; i < mapHeight; i++) {
		tile.push_back(std::vector<MapTile>());
		for (int j = 0; j < mapWidth; j++) {
			tile.at(tile.size() - 1).push_back(MapTile(0, sf::Vector2f(17.f * j, 17.f * i)));
		}
	}

	if (!buffer.loadFromFile("Assets/Music/EditorState.wav")) {
		std::cout << "Faildes to load soundBuffer\n";
	}

	music.setBuffer(buffer);
	music.play();

	music.setLoop(true);
	music.setVolume(35.f);

	if (!mouse_up.loadFromFile("Assets/Cursor/cursor.gif")) {
		std::cout << "Cannot load texture\n";
	}

	if (!mouse_down.loadFromFile("Assets/Cursor/cursor_down.gif")) {
		std::cout << "Cannot load texture\n";
	}

	buttons.push_back(Button(sf::Vector2f(700.f, 200.f), "Clear"));
	buttons.push_back(Button(sf::Vector2f(700.f, 100.f), "Save"));
	buttons.push_back(Button(sf::Vector2f(700.f, 300.f), "Load"));

	viewL = sf::View(sf::FloatRect(0, 0, 411, screenHeight));
	viewR = sf::View(sf::FloatRect(411, 0, screenWidth, screenHeight));

	viewL.setViewport(sf::FloatRect(0.f, 0.f, 0.36f, 1.f));
	viewR.setViewport(sf::FloatRect(0.36f, 0.f, 0.64f, 1.f));
	viewL.setSize(100, 117);
	zoom = 1.f;
}

void EditorState::loadTextures() {
	std::filesystem::path folder("Assets/WallTex");
	int offset = 1;
	sf::Texture texture;
	selection.push_back(MapTile(0, sf::Vector2f(600, 1), texture));
	if (std::filesystem::exists(folder) && std::filesystem::is_directory(folder)) {
		for (const auto& it : std::filesystem::directory_iterator(folder)) {
			if (std::filesystem::is_regular_file(it)) {
				if (!texture.loadFromFile(it.path().string())) {
					std::cout << "Cannot load texture\n";
				}

				selection.push_back(MapTile(selection.size(), sf::Vector2f(600, 40 * offset + 1), texture));
				offset++;
			}
		}
	} else {
		std::cout << "Folder does not exist or is not a directory." << std::endl;
	}
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

	if (zoom > 5.f) {
		zoom = 5.f;
	}

	if (zoom < 0.1f) {
		zoom = 0.1f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		viewL.move(-2.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		viewL.move(2.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		viewL.move(0.f, -2.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		viewL.move(0.f, 2.f);
	}
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

	moveView();

	if (buttons.at(0).clicked()) {
		for (auto& it : tile) {
			for (auto& it2 : it) {
				it2.rect.setTexture(nullptr);
				it2.texNum = 0;
			}
		}
	}

	if (buttons.at(1).clicked()) {
		std::fstream file("Assets/Maps/MapLay.ors", std::ios::out | std::ios::binary);

		for (auto& it : tile) {
			for (auto& it2 : it) {
				file.write(reinterpret_cast<const char*>(&it2.texNum), sizeof(it2.texNum));
			}
		}

		file.close();
	}

	if (buttons.at(2).clicked()) {
		std::fstream file("Assets/Maps/MapLay.ors", std::ios::in | std::ios::binary);

		if (file.is_open()) {
			for (int i = 0; i < mapHeight; i++) {
				for (int j = 0; j < mapWidth; j++) {
					int num = 0;
					file.read(reinterpret_cast<char*>(&num), sizeof(num));
					tile.at(i).at(j).texNum = num;
					tile.at(i).at(j).tex = selection.at(num).tex;
				}
			}
		}

		file.close();
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

	for (auto& it : tile) {
		for (auto& it2 : it) {
			if (it2.rect.getGlobalBounds().contains(sf::Vector2f(worldCoords)) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				it2.texNum = selected;
				if (selected != 0) {
					it2.tex = selection.at(selected).tex;
				} else {
					it2.rect.setTexture(nullptr);
				}
			}
		}
	}
}

void EditorState::draw(sf::RenderTarget* window) {

	window->setView(viewL);

	for (auto& it : tile) {
		for (auto& it2 : it) {
			window->draw(it2.getRect());
		}
	}

	worldCoords = window->mapPixelToCoords(sf::Vector2i(mouseCoords));

	window->setView(viewR);

	for (auto& it : selection) {
		window->draw(it.getRect());
	}

	buttons.at(0).draw(window);
	buttons.at(1).draw(window);
	buttons.at(2).draw(window);

	window->setView(window->getDefaultView());

	window->draw(mouse);
}
