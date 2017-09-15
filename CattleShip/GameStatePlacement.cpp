#include "GameStatePlacement.h"
#include "GameStateMenu.h"
#include "GameStatePlay.h"
#include "Utilities.h"
#include "AI.h"

GameStatePlacement::GameStatePlacement(Game* game) : GameState(game)
{
	placedShipIndex = -1;
	shipHorizontal = false;
	finishedPlacement = false;

	// Prepare label font
	//labelFont.loadFromFile(Utilities::getFontPath("arial.ttf"));

	// Prepare the label sprite and background sprite
	labelSprite = game->textureManager.GetSpriteBySpriteType(PlacementLabel);
	labelSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, labelSprite), 0));
	rotateSprite = game->textureManager.GetSpriteBySpriteType(RotateSprite);
	rotateSprite.setPosition(sf::Vector2f(Utilities::getCenterXOfSprite(game->window, rotateSprite) + 120, 65));
	backgroundSprite = game->textureManager.GetSpriteBySpriteType(BoardBackgroundSprite);

	// Clear the board in case it's a consecutive game
	game->playerOne.init(game->window);
	game->playerTwo.init(game->window);

	// Prepare music
	if (placementTheme.openFromFile(Utilities::getSoundfilePath("placetheme.ogg")))
	{	
		game->settings.setCurrentVolume(0);
		game->settings.setVolume(40);
		placementTheme.setVolume(game->settings.getCurrentVolume());
		placementTheme.setLoop(true);
		placementTheme.play();
	}

	game->effects.startFade(0.5f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeIn);
}

void GameStatePlacement::handleInput()
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
			if (event.mouseButton.button == sf::Mouse::Left && !finishedPlacement)
			{
				if (rotateSprite.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					shipHorizontal = !shipHorizontal;
				}
				else
					placedShipIndex = game->playerOne.board.getValidTileByCoords(sf::Vector2f(event.mouseButton.x, event.mouseButton.y),
						game->playerOne.currentShipSelection, shipHorizontal);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				// To revert selection - For debugging only
				//if (game->playerOne.currentShipSelection > 0)
				//	game->playerOne.currentShipSelection--;
			}
			break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
			{
				game->changeState(new GameStateMenu(game));
				return;
			}
			else if (event.key.code == sf::Keyboard::R)
			{
				shipHorizontal = !shipHorizontal;
			}
			break;
		}
	}
}

void GameStatePlacement::update(const float dt)
{
	// Change game state if finishedPlacement is flagged
	if (finishedPlacement)
	{
		// Clear the rectangle highlights
		game->playerOne.board.clearOutlineColors();
		
		game->effects.timers.startTimer(PlayerFinishedPlacement, 1.0f);
		if (!game->effects.timers.timerIsReady(PlayerFinishedPlacement) &&
			game->effects.timers.timerHasFinished(PlayerFinishedPlacement, dt))
		{
			// Randomly place ships for playerTwo
			game->ai.randomPlaceShips(&game->playerTwo);
			game->changeState(new GameStatePlay(game));
			return;
		}
	}

	// Change to next ship if current ship is placed
	if (placedShipIndex != -1)
	{			
		// Place the ship in the board
		game->playerOne.board.setBoardPiece(placedShipIndex, game->playerOne.currentShipSelection, shipHorizontal);
		placedShipIndex = -1;

		// Flag finishedPlacement if last ship was placed to change state in the next iteration
		// We do this to show the updated board after the last ship was placed before changing states
		if (game->playerOne.currentShipSelection == LastShip)
		{
			game->effects.startFade(0.5f, SineEaseIn, sf::Color(0, 0, 0), 0, FadeOut);
			game->settings.setVolume(0);
			finishedPlacement = true;
		}
		else
			game->playerOne.currentShipSelection++;
	}

	// Check mouse over
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(game->window));
	game->playerOne.board.checkMouseOver(mousePosition, game->playerOne.currentShipSelection, shipHorizontal);
	//game->printCoordinates(mousePosition.x, mousePosition.y);

	// Fade the music in/out if currentVolume differs from volume
	if (game->settings.adjustedVolume())
		placementTheme.setVolume(game->settings.getCurrentVolume());

	game->effects.update(dt);
}

void GameStatePlacement::render(const float dt)
{
	// Set background
	game->window.draw(backgroundSprite);

	// Show instructions text, current cattle being placed
	game->window.draw(labelSprite);

	// Display the ship type
	game->playerOne.renderCurrentShip(game->window);

	// Display the rotate button
	game->window.draw(rotateSprite);

	// Display the board
	game->playerOne.board.render(game->window, true);
	//game->window.draw(game->coordText);
	game->effects.render(game->window);

}
