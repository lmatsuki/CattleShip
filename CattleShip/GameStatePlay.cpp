#include "GameStatePlay.h"
#include "GameStateMenu.h"
#include "Utilities.h"

GameStatePlay::GameStatePlay(Game * game) : GameState(game)
{
	isGameOver = false;
	displayFoundShip = false;
	game->playerTurn = true;  // Reset when playing a new game

	// Prepare label font
	labelFont.loadFromFile(Utilities::getFontPath("arial.ttf"));

	// Prepare the label sprite and background sprite
	playerTurnSprite = game->textureManager.GetSpriteBySpriteType(PlayPlayerTurnSprite);
	playerTurnSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, playerTurnSprite), 0));
	enemyTurnSprite = game->textureManager.GetSpriteBySpriteType(PlayEnemyTurnSprite);
	enemyTurnSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, enemyTurnSprite), 0));
	backgroundSprite = game->textureManager.GetSpriteBySpriteType(BoardBackgroundSprite);

	playerWinSprite = game->textureManager.GetSpriteBySpriteType(PlayPlayerWinSprite);
	playerWinSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, playerWinSprite), 
		Utilities::getCenterOfScreen(game->window).y - 50));
	enemyWinSprite = game->textureManager.GetSpriteBySpriteType(PlayEnemyWinSprite);
	enemyWinSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, enemyWinSprite),
		Utilities::getCenterOfScreen(game->window).y - 50));
	shipFoundSprite = game->textureManager.GetSpriteBySpriteType(FoundShip);

	// Load sounds
	sound.setVolume(40);
	foundSoundBuffer.loadFromFile(Utilities::getSoundfilePath("found.wav"));
	missedSoundBuffer.loadFromFile(Utilities::getSoundfilePath("missed.wav"));

	// Prepare music
	victoryTheme.openFromFile(Utilities::getSoundfilePath("victory.ogg"));
	defeatTheme.openFromFile(Utilities::getSoundfilePath("defeat.ogg"));
	if (playTheme.openFromFile(Utilities::getSoundfilePath("playtheme.ogg")))
	{
		game->settings.setCurrentVolume(0);
		game->settings.setVolume(40);
		playTheme.setVolume(game->settings.getCurrentVolume());
		playTheme.setLoop(true);
		playTheme.play();
	}

	game->effects.startFade(0.5f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeIn);
}

GameStatePlay::~GameStatePlay()
{
}

void GameStatePlay::handleInput()
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
			if (!isGameOver)
			{
				// Prevents player from firing missles during transition
				if (event.mouseButton.button == sf::Mouse::Left && game->effects.timers.timerIsReady(PlayerOneFiredMissle) &&
					game->effects.timers.timerIsReady(PlayerOneTurnEnd))
				{
					handleCurrentPlayerClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					game->playerTurn = !game->playerTurn;
				}
			}
			else
			{
				// End game if screen is clicked and there is a winner 
				game->changeState(new GameStateMenu(game));
				return;
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
			{
				game->changeState(new GameStateMenu(game));
				return;
			}
			break;
		}
	}
}

void GameStatePlay::update(const float dt)
{
	// Skip if game is over
	if (isGameOver)
		return;
	else
	{
		// Need to check game end condition AFTER AI movement and BEFORE turn change
		if (getOtherPlayer()->areAllShipsDead())
		{
			playTheme.stop();
			isGameOver = true;
			getCurrentPlayer()->won = true;
			if (getCurrentPlayer() == &game->playerOne)
				victoryTheme.play();
			else
				defeatTheme.play();
			return;
		}
	}

	// If enemy's turn, enemy picks a random tile until it finds an unclicked tile
	// inside the board based on difficulty setting
	TileStateEnum tileState = Invalid;

	if (!game->playerTurn && game->effects.timers.timerIsReady(DelayAfterAIFires) &&
		game->effects.timers.timerIsReady(DelayAfterAIFadeOut))
	{
		game->playerTwo.timer.start(1.5f);
		if (game->playerTwo.timer.hasFinished(dt))
		{
			// Will return from function only after a valid tile is selected
			tileState = game->ai.fireBasedOnDifficulty(&game->playerOne, game->settings.getDifficulty());	
			if (tileState == Hit)
			{
				displayFoundShip = true;
				sound.setBuffer(foundSoundBuffer);
				sound.play();
				sf::Vector2f foundLocation(game->playerTwo.board.getRectangleShapePosition(game->ai.getShipFoundIndex()));
				shipFoundSprite.setPosition(foundLocation.x + 50, foundLocation.y - 50);
			}
			else
			{
				// Missed
				sound.setBuffer(missedSoundBuffer);
				sound.play();
			}
		}
	}

	// Only change turns if a valid tile was clicked by enemy
	if (tileState != Invalid || !game->effects.timers.timerIsReady(DelayAfterAIFires))
	{
		// Add a bit of delay after ai fires
		game->effects.timers.startTimer(DelayAfterAIFires, 1.0f);
		if (game->effects.timers.timerHasFinished(DelayAfterAIFires, dt))
		{
			game->effects.timers.startTimer(DelayAfterAIFadeOut, 0.5f);
			game->effects.startFade(0.5f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeOut);
		}
	}

	// Switch to player turn after DelayAfterAIFadeOut is complete
	if (!game->effects.timers.timerIsReady(DelayAfterAIFadeOut))
	{
		if (game->effects.timers.timerHasFinished(DelayAfterAIFadeOut, dt))
		{
			game->playerTurn = !game->playerTurn;
			displayFoundShip = false;
			game->effects.startFade(0.5f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeIn);
		}
	}

	// Update the timer during player's turn
	if (game->playerTurn)
	{
		// After the player fires a missle
		if (!game->effects.timers.timerIsReady(PlayerOneFiredMissle) &&
			game->effects.timers.timerHasFinished(PlayerOneFiredMissle, dt))
		{
			game->effects.timers.startTimer(PlayerOneTurnEnd, 0.75f);
			game->effects.startFade(0.5f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeOut);
		}

		// After the fade out is complete
		if (!game->effects.timers.timerIsReady(PlayerOneTurnEnd) && 
			game->effects.timers.timerHasFinished(PlayerOneTurnEnd, dt))
		{
			game->effects.startFade(0.5f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeIn);
			game->playerTurn = !game->playerTurn;
			displayFoundShip = false;
		}
	}

	// Fade the music in/out if currentVolume differs from volume
	if (game->settings.adjustedVolume())
		playTheme.setVolume(game->settings.getCurrentVolume());

	game->effects.update(dt);
}

void GameStatePlay::render(const float dt)
{
	// Display the background
	game->window.draw(backgroundSprite);

	// Display winner/loser text
	if (isGameOver)
	{
		renderWinner(getCurrentPlayer());
		return;
	}

	// Display the board & label sprite
	if (game->playerTurn)
	{
		game->playerTwo.board.render(game->window, false);
		game->window.draw(playerTurnSprite);
		//game->playerOne.board.render(game->window, true);
	}
	else
	{
		game->playerOne.board.render(game->window, true);
		game->window.draw(enemyTurnSprite);
	}

	// Draw player ship spotted sign 
	if (displayFoundShip)
		game->window.draw(shipFoundSprite);

	game->effects.render(game->window);
}

void GameStatePlay::handleCurrentPlayerClick(const sf::Vector2f mousePosition)
{
	// If player's turn, make sure the clicked position is inside the board & unclicked tile
	TileStateEnum tileState = Invalid;
	if (game->playerTurn)
		tileState = game->playerTwo.board.checkFiredPosition(mousePosition);

	if (tileState != Invalid)
	{
		// Switch turns in update after this timer ends
		game->effects.timers.startTimer(PlayerOneFiredMissle, 0.75f);
		if (tileState == Hit)
		{
			displayFoundShip = true;
			sound.setBuffer(foundSoundBuffer);
			sound.play();
			sf::Vector2f foundLocation(game->playerOne.board.getRectangleShapePosition(
				game->playerOne.board.getTileByCoords(mousePosition)));
			shipFoundSprite.setPosition(foundLocation.x + 50, foundLocation.y - 50);
		}
		else
		{
			// Missed
			sound.setBuffer(missedSoundBuffer);
			sound.play();
		}
	}
}

Player* GameStatePlay::getCurrentPlayer()
{
	if (game->playerTurn)
		return &game->playerOne;
	else
		return &game->playerTwo;
}

Player* GameStatePlay::getOtherPlayer()
{
	if (game->playerTurn)
		return &game->playerTwo;
	else
		return &game->playerOne;
}

void GameStatePlay::renderWinner(Player* player)
{
	// Set background
	game->window.draw(backgroundSprite);

	// If player 1 didn't win, player 2 must have won
	if ((player == &game->playerOne && player->won) || !player->won)
	{		
		game->window.draw(playerWinSprite);
	}
	else
	{
		game->window.draw(enemyWinSprite);
	}
}
