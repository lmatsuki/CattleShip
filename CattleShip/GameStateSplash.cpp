#include "GameStateSplash.h"
#include "GameStateMenu.h"

GameStateSplash::GameStateSplash(Game * game) : GameState(game)
{
	// Prepare title font
	splashFont.loadFromFile(Utilities::getFontPath("arial.ttf"));

	game->effects.setBackgroundColor(sf::Color::Black);
	game->effects.startFade(1, SineEaseInOut, sf::Color(0, 0, 0), 3);
}

GameStateSplash::~GameStateSplash()
{
}

void GameStateSplash::handleInput()
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
				game->changeState(new GameStateMenu(game));
				return;
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

void GameStateSplash::update(const float dt)
{
	// Move to menu if splash screen is done
	if (!game->effects.isFading())
	{
		game->changeState(new GameStateMenu(game));
		return;
	}

	// Prepare the text object
	const float centerHeight = Utilities::getCenterOfScreen(game->window).y;

	Utilities::prepareText(splashText, "ELEM SOFTWARE", splashFont, 50, sf::Text::Bold, sf::Color(70, 207, 255, 255),
		Utilities::getCenterXOfText(game->window, splashText), centerHeight - 50);

	game->effects.update(dt);
}

void GameStateSplash::render(const float dt)
{
	game->window.draw(splashText);
	game->effects.render(game->window);
}