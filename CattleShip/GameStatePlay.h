#pragma once

#include "Game.h"
#include "GameState.h"

class GameStatePlay : public GameState
{
public:
	GameStatePlay(Game* game);
	~GameStatePlay();

	virtual void handleInput();
	virtual void update(const float dt);
	virtual void render(const float dt);

	void handleCurrentPlayerClick(const sf::Vector2f mousePosition);
	Player* getCurrentPlayer();
	Player* getOtherPlayer();
	void renderWinner(Player* player);

	sf::Font labelFont;
	sf::Text labelText;

	sf::Sprite backgroundSprite;
	sf::Sprite playerTurnSprite;
	sf::Sprite enemyTurnSprite;
	sf::Sprite playerWinSprite;
	sf::Sprite enemyWinSprite;
	bool isGameOver;
};