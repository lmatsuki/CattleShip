#include "GameStatePlay.h"
#include "GameStateMenu.h"
#include "Utilities.h"

GameStatePlay::GameStatePlay(Game * game) : GameState(game)
{
	isGameOver = false;
	// Prepare label font
	labelFont.loadFromFile(Utilities::getFontPath("arial.ttf"));
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
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					handleCurrentPlayerClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					game->playerTurn = !game->playerTurn;
				}
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
	// If enemy's turn, enemy picks a random tile until it finds an unclicked tile
	// inside the board based on difficulty setting
	TileStateEnum tileState = Invalid;
	if (!game->playerTurn)
	{
		tileState = game->ai.fireBasedOnDifficulty(&game->playerOne, game->settings.getDifficulty());
	}

	// Need to check game end condition AFTER AI movment and BEFORE turn change
	if (!isGameOver && getCurrentPlayer()->areAllShipsDead())
	{
		isGameOver = true;
		getOtherPlayer()->won = true;
	}

	// Only change turns if a valid tile was clicked
	if (tileState != Invalid)
		game->playerTurn = !game->playerTurn;
}

void GameStatePlay::render(const float dt)
{
	// Show instructions text, current cattle being placed
	Utilities::renderText(labelText, game->window, "Enemy Board:", labelFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, labelText), 0);

	// Display the board
	if (game->playerTurn)
	{
		/*game->playerTwo.board.render(game->window, false);*/
		game->playerOne.board.render(game->window, true);
	}
	else
	{
		game->playerOne.board.render(game->window, true);
	}

	// Display winner/loser text
	if (isGameOver)
		renderWinner(getCurrentPlayer());

	game->window.draw(game->coordText);
}

void GameStatePlay::handleCurrentPlayerClick(const sf::Vector2f mousePosition)
{
	// If player's turn, make sure the clicked position is inside the board & unclicked tile
	TileStateEnum tileState = Invalid;
	if (game->playerTurn)
		tileState = game->playerTwo.board.checkFiredPosition(mousePosition);

	if (tileState != Invalid)
		game->playerTurn = !game->playerTurn;
}

Player* GameStatePlay::getCurrentPlayer()
{
	if (game->playerTurn)
		return &game->playerOne;
	else
		return &game->playerTwo;
}

Player * GameStatePlay::getOtherPlayer()
{
	if (game->playerTurn)
		return &game->playerTwo;
	else
		return &game->playerOne;
}

void GameStatePlay::renderWinner(Player* player)
{
	// If player 1 didn't win, player 2 must have won
	if (player == &game->playerOne && player->won)
		Utilities::renderText(labelText, game->window, "You won!!", labelFont, 80, sf::Text::Bold, sf::Color::White,
			Utilities::getCenterXOfText(game->window, labelText), Utilities::getCenterOfScreen(game->window).y);
	else
		Utilities::renderText(labelText, game->window, "You lost!!", labelFont, 80, sf::Text::Bold, sf::Color::White,
			Utilities::getCenterXOfText(game->window, labelText), Utilities::getCenterOfScreen(game->window).y);
}
