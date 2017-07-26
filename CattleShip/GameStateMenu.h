#pragma once

#include "Game.h"
#include "GameState.h"

class GameStateMenu : public GameState
{
public:
	GameStateMenu(Game* game);
	~GameStateMenu();

	virtual void handleInput();
	virtual void update(const float dt);
	virtual void render(const float dt);

	sf::Font titleFont;
	sf::Font menuFont;

	sf::Text titleText;
	sf::Text playText;
	sf::Text optionsText;
	sf::Text quitText;
};