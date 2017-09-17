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

	// Prepare the splash logo
	const float centerHeight = Utilities::getCenterOfScreen(game->window).y;
	splashSprite = game->textureManager.GetSpriteBySpriteType(SplashLogo);
	splashSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, splashSprite), centerHeight - 50));

	game->effects.update(dt);
}

void GameStateSplash::render(const float dt)
{
	game->window.draw(splashSprite);
	game->effects.render(game->window);
}