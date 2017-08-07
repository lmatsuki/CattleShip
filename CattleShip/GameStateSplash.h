#pragma once

#include "Game.h"
#include "GameState.h"

class GameStateSplash : public GameState
{
public:
	GameStateSplash(Game* game);
	~GameStateSplash();

	virtual void handleInput();
	virtual void update(const float dt);
	virtual void render(const float dt);

	sf::Font splashFont;
	sf::Text splashText;
};