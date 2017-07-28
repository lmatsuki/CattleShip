#pragma once

#include "Player.h"

class AI 
{
public:
	AI();

	void randomPlaceShips(Player* player);
	TileStateEnum randomlyFire(Player* player);

private:
	
};