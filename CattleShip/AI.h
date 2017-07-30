#pragma once

#include "Player.h"
#include "DifficultyEnum.h"

class AI 
{
public:
	AI();

	void randomPlaceShips(Player* player);
	TileStateEnum fireBasedOnDifficulty(Player* player, DifficultyEnum difficulty);
	TileStateEnum randomlyFire(Player* player);

private:
	
};