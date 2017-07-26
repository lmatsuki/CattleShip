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
	playerOne.init();
	playerOne.board.init(window);
	playerOne.board.setBoardFillColor(sf::Color::White);
	playerTwo.init();
	playerTwo.board.init(window);
	playerTwo.board.setBoardFillColor(sf::Color::White);

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
		window.clear(sf::Color::Black);
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

//void Game::Start()
//{
//	// Game is running
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
			// if (gameState == Playing)
//			{
//				// Need to check turn, handle click and show appropriate text/image if caught/missed
//				if (playerTurn)
//				{
//					if (event.type == sf::Event::MouseButtonReleased)
//					{
//						if (event.mouseButton.button == sf::Mouse::Left)
//						{
//							printCoordinates(event.mouseButton.x, event.mouseButton.y);
//							if (board.ClickedInGrid(event.mouseButton.x, event.mouseButton.y))
//							{
//								board.CheckClickedTile(playerTurn, event.mouseButton.x, event.mouseButton.y);
//								playerTurn = false;
//							}								
//						}
//					}
//				}
//				else
//				{
//					// AI's turn
//					playerTurn = true;
//				}
//			}
//		}
//
//		Render();
//	}
//}

//void Game::Render()
//{
//	window.clear(backGroundColor);
//
//	if (gameState == Playing)
//	{
//		// Display the board
//		board.Render(window, playerTurn);
//		window.draw(coordText);
//	}
//	else if (gameState == Settings)
//	{
//		// Display the settings
//		// Set difficulty
//
//	}
//	
//	window.display();
//}



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

