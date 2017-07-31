#pragma once

#include <stack>
#include "Player.h"
#include "DifficultyEnum.h"
#include "DirectionEnum.h"

class AI 
{
public:
	AI();
	~AI();

	void randomPlaceShips(Player* player);
	TileStateEnum fireBasedOnDifficulty(Player* player, DifficultyEnum difficulty);
	TileStateEnum randomlyFire(Player* player);
	TileStateEnum smartFire(Player* player, const int smartChance);

	bool noShipOnSurroundingTiles(Player* player);
	bool noEmptySurroundingTiles(Player* player);
	void updateHitShipInfo(const int tileIndex, Player* player);
	bool getSmartOrStupid(const int smartChance);
	DirectionEnum getRandomDirection();
	int getIndexOfDirection(const DirectionEnum direction, const int tileIndex);

	// fallbackTileIndex stack
	int getFallbackTileIndex();
	void clearFallbackTileIndex();

private:
	ShipTypeEnum lastHitShipType;
	int sameShipHitCount;
	int lastHitTileIndex;
	std::stack<int> fallbackTileIndex;  // If the AI goes towards to wrong direction, it can fallback to these tiles
};