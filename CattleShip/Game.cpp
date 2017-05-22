#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "GameStateEnum.h"

Game::Game() : gameState(Menu), backGroundColor(sf::Color(0, 0, 0, 255))
{
	Init();
}

void Game::Init()
{
	int status = 0;
	window.create(sf::VideoMode(800, 600), "Cattle Ship");

	if (!font.loadFromFile("font/arial.ttf"))
		status = -1;

	if (status == -1)
	{
		// Terminate the game somehow
		//window.close();
	}		
}

void Game::Start()
{
	// Game is running
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (gameState == Menu)
			{
				if (sf::Event::MouseButtonReleased)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						std::cout << "Mouse x: " << event.mouseButton.x << std::endl;
						std::cout << "Mouse y: " << event.mouseButton.y << std::endl;
					}
				}
			}
		}

		Render();
	}
}

void Game::Render()
{
	window.clear(backGroundColor);

	if (gameState == Menu)
	{
		// Display the Title
		sf::Text text("Cattle Ship", font);
		text.setCharacterSize(60);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::Green);
		text.setPosition(GetCenterOfText(text), 0);
		window.draw(text);

		// Display the options
		sf::Text text("Play", font);
		text.setCharacterSize(40);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::White);
		text.setPosition(GetCenterOfText(text), 0);
		window.draw(text);

		sf::Text text("Options", font);
		text.setCharacterSize(40);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::White);
		text.setPosition(GetCenterOfText(text), 0);
		window.draw(text);

		sf::Text text("Quit", font);
		text.setCharacterSize(40);
		text.setStyle(sf::Text::Bold);
		text.setColor(sf::Color::White);
		text.setPosition(GetCenterOfText(text), 0);
		window.draw(text);
	} 
	else if (gameState == Playing)
	{
		// Display the board

	}
	else if (gameState == Settings)
	{
		// Display the settings

	}
	
	window.display();
}

sf::Vector2f Game::GetCenterOfScreen()
{
	sf::Vector2u centerOfScreen = window.getSize();
	return sf::Vector2f(centerOfScreen.x / 2, centerOfScreen.y / 2);
}

float Game::GetCenterOfText(sf::Text const &text)
{
	float centerOfText = GetCenterOfScreen().x - text.getLocalBounds().width / 2;
	return centerOfText;
}

