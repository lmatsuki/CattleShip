#include "GameStateMenu.h"
#include "GameStatePlacement.h"
#include "Utilities.h"

GameStateMenu::GameStateMenu(Game* game) : GameState(game)
{
	// Prepare title font
	titleFont.loadFromFile(Utilities::getFontPath("arial.ttf"));
	// Prepare menu font
	menuFont.loadFromFile(Utilities::getFontPath("arial.ttf"));
}

GameStateMenu::~GameStateMenu()
{

}

void GameStateMenu::handleInput()
{
	sf::Event event;
	while (game->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				game->window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					game->printCoordinates(event.mouseButton.x, event.mouseButton.y);
					if (playText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						game->printText("Clicked Play!");
						game->changeState(new GameStatePlacement(game));
						return;
					}
					else if (optionsText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
						game->printCoordinates(0, 0);
					else if (quitText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
						game->window.close();
				}
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Escape)
				{
					game->window.close();
				}
				break;
		}	
	}
}

void GameStateMenu::update(const float dt)
{

}

void GameStateMenu::render(const float dt)
{
	const float centerHeight = Utilities::getCenterOfScreen(game->window).y;
	const float offsetY = 100.0f;

	// Display the Title
	Utilities::renderText(titleText, game->window, "Cattle Ship", titleFont, 60, sf::Text::Bold, sf::Color::Green,
		Utilities::getCenterXOfText(game->window, titleText), 0);

	// Display other buttons
	Utilities::renderText(playText, game->window, "Play", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, playText), centerHeight - offsetY);

	Utilities::renderText(optionsText, game->window, "Options", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, optionsText), centerHeight);

	Utilities::renderText(quitText, game->window, "Quit", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, quitText), centerHeight + offsetY);
	
	game->window.draw(game->coordText);
}