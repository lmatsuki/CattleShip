#pragma once

#include "Board.h"

class Player
{
public:
	Player(const int dimension, TextureManager* textureManager);
	void init();
	void renderCurrentShip(sf::RenderWindow& window);

	Board board;
	int currentShipSelection;
	TextureManager* textureManager;
};