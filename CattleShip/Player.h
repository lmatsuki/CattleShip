#pragma once

#include "Board.h"

class Player
{
public:
	Player(const int dimension, TextureManager* textureManager);
	void init();
	void renderCurrentShip(sf::RenderWindow& window);
	bool areAllShipsDead();

	bool won;
	Board board;
	int currentShipSelection;
	TextureManager* textureManager;
};