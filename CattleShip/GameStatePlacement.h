#pragma once

#include <SFML\Audio.hpp>
#include "Game.h"
#include "GameState.h"

class GameStatePlacement : public GameState
{
public:
	GameStatePlacement(Game* game);

	virtual void handleInput();
	virtual void update(const float dt);
	virtual void render(const float dt);

private:
	int placedShipIndex;
	bool shipHorizontal;
	bool finishedPlacement;
	//sf::Font labelFont;
	//sf::Text labelText;

	sf::Sprite backgroundSprite;
	sf::Sprite labelSprite;
	sf::Sprite rotateSprite;

	// Music
	sf::Music placementTheme;
};
