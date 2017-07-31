#include "GameStateMenu.h"
#include "GameStatePlacement.h"
#include "Utilities.h"

GameStateMenu::GameStateMenu(Game* game) : displaySettings(false), initialized(false), GameState(game)
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
					if (handleLeftClick(event.mouseButton.x, event.mouseButton.y))
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

void GameStateMenu::update(const float dt)
{

}

void GameStateMenu::render(const float dt)
{
	if (!initialized)
		initialize();

	// Display the Title
	game->window.draw(titleText);

	if (displaySettings)
	{
		game->window.draw(settingsText);
		game->window.draw(easyText);
		game->window.draw(mediumText);
		game->window.draw(hardText);
		game->window.draw(backText);
	}
	else
	{
		// Display other buttons
		game->window.draw(playText);
		game->window.draw(optionsText);
		game->window.draw(quitText);
	}

	// Need to initialize twice to reposition items correctly
	if (!initialized)
	{
		initialize();
		initialized = true;
	}
	
	//game->window.draw(game->coordText);
}

void GameStateMenu::initialize()
{
	// Prepare the text objects
	const float centerHeight = Utilities::getCenterOfScreen(game->window).y;
	const float offsetY = 100.0f;

	Utilities::prepareText(titleText, "Cattle Ship", titleFont, 60, sf::Text::Bold, sf::Color::Green,
		Utilities::getCenterXOfText(game->window, titleText), 0);

	Utilities::prepareText(settingsText, "Settings", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, settingsText), centerHeight - offsetY);

	Utilities::prepareText(easyText, "Easy", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, easyText) - 200, centerHeight);

	Utilities::prepareText(mediumText, "Medium", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, mediumText), centerHeight);

	Utilities::prepareText(hardText, "Hard", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, hardText) + 200, centerHeight);

	Utilities::prepareText(backText, "Back", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, backText), centerHeight + offsetY);

	Utilities::prepareText(playText, "Play", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, playText), centerHeight - offsetY);

	Utilities::prepareText(optionsText, "Options", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, optionsText), centerHeight);

	Utilities::prepareText(quitText, "Quit", menuFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, quitText), centerHeight + offsetY);

	Utilities::selectDifficulty(easyText, mediumText, hardText);
}

// If it returns true, that means it must return.
bool GameStateMenu::handleLeftClick(const int x, const int y)
{
	//game->printCoordinates(x, y);
	if (displaySettings)
	{
		if (easyText.getGlobalBounds().contains(x, y))
		{
			game->settings.setDifficulty(Easy);
			Utilities::selectDifficulty(easyText, mediumText, hardText);
		}
		else if (mediumText.getGlobalBounds().contains(x, y))
		{
			game->settings.setDifficulty(Medium);
			Utilities::selectDifficulty(mediumText, easyText, hardText);
		}
		else if (hardText.getGlobalBounds().contains(x, y))
		{
			game->settings.setDifficulty(Hard);
			Utilities::selectDifficulty(hardText, easyText, mediumText);
		}
		else if (backText.getGlobalBounds().contains(x, y))
		{
			displaySettings = false;
		}
	}
	else
	{
		if (playText.getGlobalBounds().contains(x, y))
		{
			//game->printText("Clicked Play!");
			game->changeState(new GameStatePlacement(game));
			return true;
		}
		else if (optionsText.getGlobalBounds().contains(x, y))
		{
			displaySettings = true;
		}
		else if (quitText.getGlobalBounds().contains(x, y))
			game->window.close();
	}

	return false;
}
