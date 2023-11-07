#include "Game.h"

void Game::initWindow() {
	sf::VideoMode videoMode = sf::VideoMode(640.f, 480.f);
	auto windowStyle = sf::Style::Default;
	std::string windowTitle = "RPO Igra";

	window = new sf::RenderWindow(videoMode, windowTitle, windowStyle);

	shape.setRadius(100.f);
	shape.setFillColor(sf::Color::Green);
}

void Game::draw() {
	//clear
	window->clear();

	//draw
	window->draw(shape);

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
}

Game::Game() {
	initWindow();
}

Game::~Game() {
	delete window;
}

void Game::run() {
	while (window->isOpen()) {
		update();
		draw();
	}
}
