#pragma once

#include "Board.h"
#include "Timer.h"

class Player
{
public:
	Player(const int dimension, TextureManager* textureManager);
	void init(const sf::RenderWindow& window);
	void renderCurrentShip(sf::RenderWindow& window);
	bool areAllShipsDead();

	bool won;
	Board board;
	int currentShipSelection;
	TextureManager* textureManager;
	Timer timer;
};