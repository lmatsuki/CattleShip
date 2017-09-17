#include "GameStateMenu.h"
#include "GameStatePlacement.h"
#include "Utilities.h"

GameStateMenu::GameStateMenu(Game* game) : displaySettings(false), displayCredits(false), 
	initialized(false), GameState(game), starting(false)
{
	// Prepare title font
	//titleFont.loadFromFile(Utilities::getFontPath("arial.ttf"));
	// Prepare menu font
	menuFont.loadFromFile(Utilities::getFontPath("arial.ttf"));

	// Prepare music
	if (menuTheme.openFromFile(Utilities::getSoundfilePath("menutheme.ogg")))
	{
		game->settings.setCurrentVolume(0);
		game->settings.setVolume(40);
		menuTheme.setVolume(game->settings.getCurrentVolume());
		menuTheme.setLoop(true);
		menuTheme.play();
	}

	game->effects.startFade(0.5f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeIn);
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
					if (!starting && handleLeftClick(event.mouseButton.x, event.mouseButton.y))
					{
						starting = true;
						game->effects.startFade(1.0f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeOut);
						game->settings.setVolume(0);
					}
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
	game->printText(game->effects.getElapsedTime());
	game->effects.update(dt);

	// Transition to ship placement after fade out animation is complete
	if (starting && !game->effects.isFading())
	{
		menuTheme.stop();
		game->changeState(new GameStatePlacement(game));
		return;
	}

	// Fade the music in/out if currentVolume differs from volume
	if (game->settings.adjustedVolume())
		menuTheme.setVolume(game->settings.getCurrentVolume());
}

void GameStateMenu::render(const float dt)
{
	if (!initialized)
		initialize();

	// Display the background
	game->window.draw(backgroundSprite);

	// Display the Title
	game->window.draw(titleSprite);

	if (displaySettings)
	{
		game->window.draw(easySprite);
		game->window.draw(mediumSprite);
		game->window.draw(hardSprite);
		game->window.draw(backSprite);

		game->window.draw(settingsSprite);

		//game->window.draw(easyText);
		//game->window.draw(mediumText);
		//game->window.draw(hardText);
		//game->window.draw(backText);
		//game->window.draw(settingsText);
	}
	else if (displayCredits)
	{
		game->window.draw(creditNamesSprite);
		game->window.draw(backSprite);
	}
	else
	{
		// Display other buttons
		game->window.draw(playSprite);
		game->window.draw(optionsSprite);
		game->window.draw(creditsSprite);
		game->window.draw(quitSprite);
		//game->window.draw(playText);
		//game->window.draw(optionsText);
		//game->window.draw(quitText);
	}

	// Need to initialize twice to reposition items correctly
	if (!initialized)
	{
		initialize();
		initialized = true;
	}
	
	//game->window.draw(game->coordText);
	game->effects.render(game->window);
}

void GameStateMenu::initialize()
{
	// Prepare the text objects
	const float centerHeight = Utilities::getCenterOfScreen(game->window).y - 50;
	const float offsetY = 100.0f;

	titleSprite = game->textureManager.GetSpriteBySpriteType(MenuTitle);
	titleSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, titleSprite), 0));

	settingsSprite = game->textureManager.GetSpriteBySpriteType(MenuSettings);
	settingsSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, settingsSprite), centerHeight - offsetY + 50));

	//Utilities::prepareText(titleText, "Cattle Ship", titleFont, 60, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, titleText), 0);
	//Utilities::prepareText(settingsText, "Settings", menuFont, 40, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, settingsText), centerHeight - offsetY);

	// Difficulties
	backSprite = game->textureManager.GetSpriteBySpriteType(MenuBack);
	backSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, backSprite), centerHeight + offsetY + 50));

	easySprite = game->textureManager.GetSpriteBySpriteType(MenuEasy);
	easySprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, easySprite) - 200, centerHeight));

	mediumSprite = game->textureManager.GetSpriteBySpriteType(MenuMedium);
	mediumSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, mediumSprite), centerHeight));

	hardSprite = game->textureManager.GetSpriteBySpriteType(MenuHard);
	hardSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, hardSprite) + 200, centerHeight));

	//Utilities::prepareText(easyText, "Easy", menuFont, 40, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, easyText) - 200, centerHeight);
	//Utilities::prepareText(mediumText, "Medium", menuFont, 40, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, mediumText), centerHeight);
	//Utilities::prepareText(hardText, "Hard", menuFont, 40, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, hardText) + 200, centerHeight);
	//Utilities::prepareText(backText, "Back", menuFont, 40, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, backText), centerHeight + offsetY);

	// Main buttons
	playSprite = game->textureManager.GetSpriteBySpriteType(MenuPlay);
	playSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, playSprite), centerHeight - offsetY));

	optionsSprite = game->textureManager.GetSpriteBySpriteType(MenuOptions);
	optionsSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, optionsSprite), centerHeight));

	creditsSprite = game->textureManager.GetSpriteBySpriteType(MenuCredits);
	creditsSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, creditsSprite), centerHeight + offsetY));

	quitSprite = game->textureManager.GetSpriteBySpriteType(MenuExit);
	quitSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, quitSprite), centerHeight + (2 * offsetY)));

	// Credit names
	creditNamesSprite = game->textureManager.GetSpriteBySpriteType(MenuCreditNames);
	creditNamesSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, creditNamesSprite), centerHeight - 125));

	// Set selected difficulty based on setting
	DifficultyEnum currentDifficulty = game->settings.getDifficulty();
	if (currentDifficulty == Easy)
		Utilities::selectDifficulty(easySprite, mediumSprite, hardSprite, MenuEasySelected, &game->textureManager, &game->window);
	else if (currentDifficulty == Medium)
		Utilities::selectDifficulty(easySprite, mediumSprite, hardSprite, MenuMediumSelected, &game->textureManager, &game->window);
	else if (currentDifficulty == Hard)
		Utilities::selectDifficulty(easySprite, mediumSprite, hardSprite, MenuHardSelected, &game->textureManager, &game->window);

	//Utilities::selectDifficulty(easyText, mediumText, hardText);

	backgroundSprite = game->textureManager.GetSpriteBySpriteType(MenuBackground);

	//Utilities::prepareText(playText, "Play", menuFont, 40, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, playText), centerHeight - offsetY);
	//Utilities::prepareText(optionsText, "Options", menuFont, 40, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, optionsText), centerHeight);
	//Utilities::prepareText(quitText, "Quit", menuFont, 40, sf::Text::Bold, sf::Color::White,
	//	Utilities::getCenterXOfText(game->window, quitText), centerHeight + offsetY);
}

// If it returns true, that means it must return.
bool GameStateMenu::handleLeftClick(const int x, const int y)
{
	//game->printCoordinates(x, y);
	if (displaySettings)
	{
		if (easySprite.getGlobalBounds().contains(x, y))
		{
			game->settings.setDifficulty(Easy);
			Utilities::selectDifficulty(easySprite, mediumSprite, hardSprite, MenuEasySelected, &game->textureManager, &game->window);
			//Utilities::selectDifficulty(easyText, mediumText, hardText);
			game->soundManager.playSound(SetDifficultySoundBuffer);
		}
		else if (mediumSprite.getGlobalBounds().contains(x, y))
		{
			game->settings.setDifficulty(Medium);
			Utilities::selectDifficulty(easySprite, mediumSprite, hardSprite, MenuMediumSelected, &game->textureManager, &game->window);
			//Utilities::selectDifficulty(mediumText, easyText, hardText);
			game->soundManager.playSound(SetDifficultySoundBuffer);
		}
		else if (hardSprite.getGlobalBounds().contains(x, y))
		{
			game->settings.setDifficulty(Hard);
			Utilities::selectDifficulty(easySprite, mediumSprite, hardSprite, MenuHardSelected, &game->textureManager, &game->window);
			//Utilities::selectDifficulty(hardText, easyText, mediumText);
			game->soundManager.playSound(SetDifficultySoundBuffer);
		}
		else if (backSprite.getGlobalBounds().contains(x, y))
		{
			displaySettings = false;
			game->soundManager.playSound(ButtonClickSoundBuffer);
		}
	}
	else if (displayCredits)
	{
		if (backSprite.getGlobalBounds().contains(x, y))
		{
			displayCredits = false;
			game->soundManager.playSound(ButtonClickSoundBuffer);
		}
	}
	else
	{
		if (playSprite.getGlobalBounds().contains(x, y))
		{
			game->soundManager.playSound(StartGameSoundBuffer);
			return true;
		}
		else if (creditsSprite.getGlobalBounds().contains(x, y))
		{
			displayCredits = true;
			game->soundManager.playSound(ButtonClickSoundBuffer);
		}
		else if (optionsSprite.getGlobalBounds().contains(x, y))
		{
			displaySettings = true;
			game->soundManager.playSound(ButtonClickSoundBuffer);
		}
		else if (quitSprite.getGlobalBounds().contains(x, y))
		{
			game->window.close();
		}
	}

	return false;
}
