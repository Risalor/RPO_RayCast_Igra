#include "Game.h"

void Game::initWindow() {
	sf::VideoMode videoMode = sf::VideoMode(720.f, 480.f);
	auto windowStyle = sf::Style::Default;
	std::string windowTitle = "RPO Igra";

	window = new sf::RenderWindow(videoMode, windowTitle, windowStyle);
	window->setFramerateLimit(60);

	states.push(new GamePlayState());
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
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}

	states.top()->update(0.01f);
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
	while (window->isOpen()) {
		update();
		draw();
	}
}
