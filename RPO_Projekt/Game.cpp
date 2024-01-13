#include "Game.h"

void Game::initWindow() {
	sf::VideoMode videoMode = sf::VideoMode(screenWidth + 411.42f, screenHeight);
	auto windowStyle = sf::Style::Default;
	std::string windowTitle = "RPO Igra";

	window = new sf::RenderWindow(videoMode, windowTitle, windowStyle);
	window->setFramerateLimit(60);
	window->setMouseCursorVisible(false);

	states.push(new MainMenuState());
}

void Game::draw() {
	//clear
	window->clear();

	//draw
	states.top()->draw(window);

	//display
	window->display();
}

void Game::update() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}
	states.top()->update(deltaTime, window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}

void Game::manageStates() {
	switch (states.top()->getTrigger()) {
	case StateTrigger::END_GAME:
		while (states.empty()) {
			delete states.top();
			states.pop();
		}
		window->close();
		break;
	case StateTrigger::START_GAME:
		states.top()->setTrigger(StateTrigger::NO_TRIGGER);
		states.push(new GamePlayState());
		break;
	case StateTrigger::END_STATE:
		delete states.top();
		states.pop();
		if (states.empty()) {
			window->close();
		}
		break;
	case StateTrigger::START_EDITOR:
		states.top()->setTrigger(StateTrigger::NO_TRIGGER);
		states.push(new EditorState());
		break;
	default:
		break;
	}
}

Game::Game() {
	initWindow();
}

Game::~Game() {
	delete window;
	delete states.top();
	states.pop();
}

void Game::run() {
	sf::Clock cl;
	while (window->isOpen()) {
		update();
		draw();
		deltaTime = cl.restart().asSeconds();
		manageStates();
		//std::cout << deltaTime << "\n";
	}
}
