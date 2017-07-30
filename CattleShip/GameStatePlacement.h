#pragma once

#include "Game.h"
#include "GameState.h"

class GameStatePlacement : public GameState
{
public:
	GameStatePlacement(Game* game);

	virtual void handleInput();
	virtual void update(const float dt);
	virtual void render(const float dt);

	int placedShipIndex;
	bool shipHorizontal;
	bool finishedPlacement;
	sf::Font labelFont;
	sf::Text labelText;
};