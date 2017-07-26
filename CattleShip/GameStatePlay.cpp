#include "GameStatePlay.h"
#include "GameStateMenu.h"
#include "Utilities.h"

GameStatePlay::GameStatePlay(Game * game) : GameState(game)
{
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
			if (event.mouseButton.button == sf::Mouse::Left)
			{								
				handleCurrentPlayerClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{

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

}

void GameStatePlay::render(const float dt)
{
	// Show instructions text, current cattle being placed
	Utilities::renderText(labelText, game->window, "Enemy Board:", labelFont, 40, sf::Text::Bold, sf::Color::White,
		Utilities::getCenterXOfText(game->window, labelText), 0);

	// Display the board
	if (game->playerTurn)
	{
		game->playerTwo.board.render(game->window);
	}
	else
	{
		game->playerOne.board.render(game->window);
	}

	game->window.draw(game->coordText);
}

void GameStatePlay::handleCurrentPlayerClick(const sf::Vector2f mousePosition)
{
	// If player's turn, make sure the clicked position is inside the board & unclicked tile
	TileStateEnum tileState = Invalid;
	if (game->playerTurn)
		tileState = game->playerTwo.board.checkFiredPosition(mousePosition);

	// Otherwise if enemy's turn, enemy picks a random tile until it finds an unclicked tile
	// inside the board based on difficulty setting		

	// Only change turns if a valid tile was clicked
	//if (tileState != Invalid)
	//	game->playerTurn = !game->playerTurn;
	return;
}
