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
	labelFont.loadFromFile(Utilities::getFontPath("arial.ttf"));

	// Clear the board in case it's a consecutive game
	game->playerOne.init(game->window);
	game->playerTwo.init(game->window);
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
			if (event.mouseButton.button == sf::Mouse::Left)
			{
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

		// Randomly place ships for placeTwo
		game->ai.randomPlaceShips(&game->playerTwo);
		game->changeState(new GameStatePlay(game));
		return;
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
			finishedPlacement = true;
		else
			game->playerOne.currentShipSelection++;
	}

	// Check mouse over
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(game->window));
	game->playerOne.board.checkMouseOver(mousePosition, game->playerOne.currentShipSelection, shipHorizontal);
	game->printCoordinates(mousePosition.x, mousePosition.y);
}

void GameStatePlacement::render(const float dt)
{
	// Show instructions text, current cattle being placed
	Utilities::renderText(labelText, game->window, "Place your cattle!", labelFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, labelText), 0);

	// Display the ship type
	game->playerOne.renderCurrentShip(game->window);

	// Display the board
	game->playerOne.board.render(game->window, true);
	game->window.draw(game->coordText);
}
