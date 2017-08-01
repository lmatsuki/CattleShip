#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameStateMenu.h"
#include "Utilities.h"


Game::Game() : backGroundColor(sf::Color::Black), playerOne(10, &textureManager),
	playerTurn(true), playerTwo(10, &textureManager)
{
	pushState(new GameStateMenu(this));
	init();	
}

Game::~Game()
{
	while (!states.empty())
		popState();
}

void Game::init()
{
	int status = 0;
	window.create(sf::VideoMode(800, 600), "Cattle Ship", sf::Style::Close);
	window.setFramerateLimit(60);

	if (!font.loadFromFile(Utilities::getFontPath("arial.ttf")))
		status = -1;

	// Create the board	for both players
	playerOne.init(window);
	playerTwo.init(window);

	// Terminate the game somehow
	if (status == -1)
		window.close();

	// For Debugging
	coordText.setString("Coordinates..");
	coordText.setFont(font);
}

void Game::gameLoop()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		float dt = elapsed.asSeconds();

		if (peekState() == nullptr)
			continue;
		peekState()->handleInput();
		peekState()->update(dt);
		window.clear(backGroundColor);
		peekState()->render(dt);
		window.display();
	}
}

void Game::pushState(GameState* state)
{
	states.push(state);
}

void Game::popState()
{
	GameState* currentState = states.top();
	states.pop();
	delete currentState;
}

void Game::changeState(GameState* state)
{
	if (!states.empty())
		popState();
	pushState(state);
}

GameState* Game::peekState()
{
	if (states.empty())
		return nullptr;
	return states.top();
}

// For Debugging purposes
void Game::printCoordinates(int x, int y)
{
	std::ostringstream oss, oss2;
	oss << x;
	std::string mouseX = "Mouse x: " + oss.str();
	oss2 << y;
	std::string mouseY = "Mouse y: " + oss2.str();
	coordText.setString(mouseX + " : " + mouseY);
	coordText.setCharacterSize(25);
	coordText.setStyle(sf::Text::Bold);
	coordText.setFillColor(sf::Color::White);
	coordText.setPosition(0, 0);
}

void Game::printText(const std::string& text)
{
	coordText.setString(text);
	coordText.setCharacterSize(25);
	coordText.setStyle(sf::Text::Bold);
	coordText.setFillColor(sf::Color::White);
	coordText.setPosition(0, 0);
}

